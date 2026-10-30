#!/usr/bin/env python3
"""Build the legacy display stub archive.

bsd_init references native_legacy_display_probe() and
native_legacy_display_late_probe() unconditionally, but the real archive
(build-native-legacy-display.py) needs a prelink candidate that cannot exist
before the kernel links.

Stage A of the bootstrap links a kernel without the storage and display stacks;
this archive supplies just those two symbols so it can link. CONFIG_XNU_EXTRA_LD_ARCHIVES
points at the result.
"""
import json
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'build/legacy-stub'
OUT.mkdir(parents=True, exist_ok=True)

record = json.loads((ROOT / 'build/xnu/ios-obj/DEVELOPMENT_ARM64_BCM2837/bsd/DEVELOPMENT/kern_exec.o.json')
                    .read_text().strip().rstrip(','))
source = ROOT / 'kits/sheng/LegacyDisplayStub.c'
obj = OUT / 'LegacyDisplayStub.o'

command = []
args = record['arguments']
i = 0
while i < len(args):
    arg = args[i]
    if arg == record['file']:
        command.append(str(source))
    elif arg in ('-o', '-MF', '-MT', '-MJ'):
        if arg == '-o':
            command += ['-o', str(obj)]
        i += 1
    elif arg == '-Xclang' and args[i + 1].startswith('-W'):
        i += 1
    elif not arg.startswith('-W'):
        command.append(arg)
    i += 1
command += ['-mgeneral-regs-only', '-Wall', '-Wextra', '-Werror']
subprocess.run(command, cwd=record['directory'], check=True, timeout=90)

# The boot-progress overlay calls the touch and cpufreq probes; stage A links
# before those archives exist, so the package's own stubs answer for them.
stubs = ROOT / 'kits/sheng/StageAStorageStubs.c'
objs = [obj]
if stubs.is_file():
    stub_obj = OUT / 'StageAStorageStubs.o'
    stub_cmd = [str(obj) if str(a) == str(source) else str(a) for a in command[:command.index(str(OUT / 'LegacyDisplayStub.o'))]]
    stub_cmd = [str(stubs) if c == str(source) else c for c in stub_cmd]
    stub_cmd = [str(stub_obj) if c == str(OUT / 'LegacyDisplayStub.o') else c for c in stub_cmd]
    subprocess.run(stub_cmd, cwd=record['directory'], check=True, timeout=90)
    objs.append(stub_obj)

archive = OUT / 'libLegacyStub.a'
archive.unlink(missing_ok=True)
subprocess.run(['xcrun', 'ar', 'rcs', str(archive)] + [str(o) for o in objs], check=True, timeout=30)
print(f'legacy stub archive: {archive} ({len(objs)} objects)')
