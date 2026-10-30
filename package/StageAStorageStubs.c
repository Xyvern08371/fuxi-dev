/*
 * Stage 2a definitions for the symbols the kernel references but this board does
 * not build yet: the storage transports, the owner root, the touch input probe,
 * the RAM block device and the legacy display transfer.
 *
 * Boot progress links with the audited UFS driver, the owner-root code and the
 * virtio transport selected (see build-xnu-4k-baseline.sh), and it reads the
 * counters of every other subsystem it can show. The archives that normally
 * answer them are research instruments: build-native-virtio-bindings.py needs a
 * live storage capture and build-verified-root-probe.py needs a completed
 * verification of the original OS volume. Neither input exists in a clean
 * checkout.
 *
 * The references in BootProgress.c are marked weak_import, but the kernel is
 * linked as a static Mach-O, where ld64 still requires every reference to be
 * defined; hence the definitions below rather than a linker flag.
 *
 * Nothing here reports success:
 *   - fuxi has no virtio block device and no RAM block device, so their counters
 *     stay zero and boot progress takes its UFS branch;
 *   - the owner root has no policy bundle and no trusted key on this board, so
 *     vr_open() (kits/VerifiedRoot, linked from its real sources) refuses every
 *     volume instead of accepting one;
 *   - there is no touch driver yet, so the touch rows are empty and the count is
 *     zero, which is what the overlay draws;
 *   - the sheng PMGR power driver is an instrument of its own, so the poll is a
 *     no-op and the cpufreq row stays empty.
 *
 * Replace the definitions here with the real archives once their inputs exist;
 * until then they make the absence explicit instead of hiding it.
 */
#include <stddef.h>
#include <stdint.h>

/* BootProgress.c reads these as plain variables; zero means "no virtio". */
volatile uint32_t native_virtio_ready;
volatile uint32_t native_virtio_read_requests;
volatile uint32_t native_virtio_read_failures;
volatile uint64_t native_virtio_verified_blocks;

/* No RAM block device on this board either. */
volatile uint32_t native_ram_block_sparse;
volatile uint64_t native_ram_block_bytes;
volatile uint64_t native_ram_block_resident_bytes;

/* No touch controller driver: the overlay has no rows and no samples. */
char native_touch_rows[4][120];
volatile uint32_t native_touch_seq;
volatile uint32_t native_touch_count;
volatile int native_touch_xs[12];
volatile int native_touch_ys[12];
volatile uint32_t native_touch_stage_req;

/* The legacy display probe is stubbed out (LegacyDisplayStub.c), so it never
   transfers anything and never reports a status. */
volatile int native_legacy_transfer_status;

/* The owner-root mount path did not accept a volume. */
volatile int native_owner_root_accepted;

/* The policy table the owner-root mount path walks: no entries, no trusted key.
   verified_root_key is VR_KEY_BYTES of zeroes, which fails the kit's own magic
   and key checks, so vr_open() fails closed. */
const uint64_t verified_root_policy_count = 0;
const uint64_t verified_root_policies[2] = {0, 0};
const uint8_t verified_root_key[395];

/* Declared weakly by BootProgress.c, so an absent definition must still link. */
void
sheng_cpufreq_poll (
  void
  )
{
}





int native_accelerator_probe(void) { return 0; }
int native_adreno_firmware_probe(void) { return 0; }
int native_adreno_pm4_probe(void) { return 0; }
int native_aks_call(void) { return 0; }
int native_aks_lock_state(void) { return 0; }
int native_aks_opened(void) { return 0; }
int native_aks_state_enabled(void) { return 0; }
int native_constants_probe(void) { return 0; }
int native_hid_input_observed(void) { return 0; }
int native_hid_input_probe(void) { return 0; }
int native_hid_input_requested(void) { return 0; }
int native_keyevents_open_refused(void) { return 0; }
int native_keyevents_probe(void) { return 0; }
int native_keystore_probe(void) { return 0; }
int native_legacy_display_late_probe(void) { return 0; }
int native_legacy_display_probe(void) { return 0; }
int native_metal_runtime_diagnostic(void) { return 0; }
int native_mobile_display_provider_probe(void) { return 0; }
int native_original_client_probe(void) { return 0; }
int native_original_provider_descriptor(void) { return 0; }
int native_original_provider_probe(void) { return 0; }
int native_smmu4k_probe(void) { return 0; }
int sheng_boot_setup_reset(void) { return 0; }
int sheng_boot_watchdog_policy(void) { return 0; }

volatile unsigned char native_verified_block_manifest_sha384[48];
volatile int native_verified_block_root_authorized;
volatile uint64_t native_verified_block_volume_device;

/* stage-A fallbacks: one definition per symbol, generated from package/ */
__attribute__((weak)) volatile uint64_t aks_count;
__attribute__((weak)) int aks_publish(void) { return 0; }
__attribute__((weak)) volatile uint64_t aks_rc;
__attribute__((weak)) int append_job(void) { return 0; }
__attribute__((weak)) int armcpu_spi_attach(void) { return 0; }
__attribute__((weak)) volatile uint64_t banner_load;
__attribute__((weak)) volatile uint64_t bind_base;
__attribute__((weak)) volatile uint64_t boot_log_buffer;
__attribute__((weak)) int boot_log_crash_collect(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_log_crash_magic;
__attribute__((weak)) int boot_log_crash_store(void) { return 0; }
__attribute__((weak)) int boot_log_export_put(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_log_first_lba;
__attribute__((weak)) volatile uint64_t boot_log_retry_started;
__attribute__((weak)) int boot_log_retry_thread(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_log_started;
__attribute__((weak)) int boot_log_tick(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_process_attempts;
__attribute__((weak)) volatile uint64_t boot_process_busy;
__attribute__((weak)) int boot_process_capture(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_process_passes;
__attribute__((weak)) volatile uint64_t boot_process_seen;
__attribute__((weak)) int boot_process_snapshot(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_progress_banner_rows;
__attribute__((weak)) int boot_progress_bind(void) { return 0; }
__attribute__((weak)) int boot_progress_cancel_scanout(void) { return 0; }
__attribute__((weak)) int boot_progress_critical_exit(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_progress_display_owned;
__attribute__((weak)) int boot_progress_exit(void) { return 0; }
__attribute__((weak)) int boot_progress_exit_fault(void) { return 0; }
__attribute__((weak)) int boot_progress_exit_reason(void) { return 0; }
__attribute__((weak)) int boot_progress_init(void) { return 0; }
__attribute__((weak)) int boot_progress_irq(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_progress_last_pc;
__attribute__((weak)) volatile uint64_t boot_progress_observation;
__attribute__((weak)) volatile uint64_t boot_progress_panic_text;
__attribute__((weak)) volatile uint64_t boot_progress_panic_vinfo;
__attribute__((weak)) int boot_progress_poll(void) { return 0; }
__attribute__((weak)) int boot_progress_prepare_scanout(void) { return 0; }
__attribute__((weak)) int boot_progress_process_stage(void) { return 0; }
__attribute__((weak)) int boot_progress_profile_rows(void) { return 0; }
__attribute__((weak)) int boot_progress_pulse_anchor(void) { return 0; }
__attribute__((weak)) int boot_progress_putc(void) { return 0; }
__attribute__((weak)) int boot_progress_stage(void) { return 0; }
__attribute__((weak)) int boot_progress_start(void) { return 0; }
__attribute__((weak)) int boot_progress_user_abort(void) { return 0; }
__attribute__((weak)) int boot_reset_bootloader(void) { return 0; }
__attribute__((weak)) int boot_reset_probe(void) { return 0; }
__attribute__((weak)) int boot_ui_trace_begin(void) { return 0; }
__attribute__((weak)) int boot_ui_trace_hot_rows(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_ui_trace_index;
__attribute__((weak)) volatile uint64_t boot_ui_trace_label;
__attribute__((weak)) volatile uint64_t boot_ui_trace_phase;
__attribute__((weak)) int boot_ui_trace_publish(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_ui_trace_ready;
__attribute__((weak)) int boot_ui_trace_role_peer(void) { return 0; }
__attribute__((weak)) int boot_ui_trace_role_rows(void) { return 0; }
__attribute__((weak)) volatile uint64_t boot_ui_trace_rows;
__attribute__((weak)) int boot_ui_trace_snapshot(void) { return 0; }
__attribute__((weak)) int boot_ui_trace_task(void) { return 0; }
__attribute__((weak)) int bp_char(void) { return 0; }
__attribute__((weak)) int bp_clear(void) { return 0; }
__attribute__((weak)) int bp_copy(void) { return 0; }
__attribute__((weak)) int bp_exit_add(void) { return 0; }
__attribute__((weak)) int bp_heap_sort(void) { return 0; }
__attribute__((weak)) volatile uint64_t bp_kern_head;
__attribute__((weak)) int bp_kernel_chain(void) { return 0; }
__attribute__((weak)) int bp_line(void) { return 0; }
__attribute__((weak)) int bp_line_bg(void) { return 0; }
__attribute__((weak)) int bp_panic_bind(void) { return 0; }
__attribute__((weak)) int bp_poll(void) { return 0; }
__attribute__((weak)) volatile uint64_t bp_prof;
__attribute__((weak)) volatile uint64_t bp_prof_head;
__attribute__((weak)) int bp_pulse_close(void) { return 0; }
__attribute__((weak)) int bp_pulse_enter(void) { return 0; }
__attribute__((weak)) int bp_pulse_leave(void) { return 0; }
__attribute__((weak)) int bp_pulse_register(void) { return 0; }
__attribute__((weak)) int bp_stage(void) { return 0; }
__attribute__((weak)) int br_find(void) { return 0; }
__attribute__((weak)) int br_read8(void) { return 0; }
__attribute__((weak)) int br_set_bootloader(void) { return 0; }
__attribute__((weak)) int br_wait(void) { return 0; }
__attribute__((weak)) int br_write8(void) { return 0; }
__attribute__((weak)) int bt_add(void) { return 0; }
__attribute__((weak)) int bt_address(void) { return 0; }
__attribute__((weak)) int bt_format(void) { return 0; }
__attribute__((weak)) int bt_kernel_stack(void) { return 0; }
__attribute__((weak)) int bt_main_rows(void) { return 0; }
__attribute__((weak)) int bt_role_char(void) { return 0; }
__attribute__((weak)) int bt_rows(void) { return 0; }
__attribute__((weak)) int bt_same(void) { return 0; }
__attribute__((weak)) int bt_user(void) { return 0; }
__attribute__((weak)) int bt_walk(void) { return 0; }
__attribute__((weak)) int bt_walk_n(void) { return 0; }
__attribute__((weak)) volatile uint64_t build_tag;
__attribute__((weak)) int capture_exception(void) { return 0; }
__attribute__((weak)) int capture_required(void) { return 0; }
__attribute__((weak)) int check_faults(void) { return 0; }
__attribute__((weak)) volatile uint64_t chrono_focus_initialized;
__attribute__((weak)) int clk_base(void) { return 0; }
__attribute__((weak)) int clk_tests(void) { return 0; }
__attribute__((weak)) int cold_start(void) { return 0; }
__attribute__((weak)) int copy_msgbuf(void) { return 0; }
__attribute__((weak)) int core_offset(void) { return 0; }
__attribute__((weak)) int core_read(void) { return 0; }
__attribute__((weak)) int core_write(void) { return 0; }
__attribute__((weak)) int crash_banner(void) { return 0; }
__attribute__((weak)) volatile uint64_t crash_bytes;
__attribute__((weak)) volatile uint64_t crash_generation;
__attribute__((weak)) volatile uint64_t crash_name;
__attribute__((weak)) int exact_digest(void) { return 0; }
__attribute__((weak)) volatile uint64_t export_lock;
__attribute__((weak)) volatile uint64_t export_region;
__attribute__((weak)) volatile uint64_t export_stage;
__attribute__((weak)) volatile uint64_t ext_bound_seen;
__attribute__((weak)) int ext_data_rows(void) { return 0; }
__attribute__((weak)) int ext_overlay_locked(void) { return 0; }
__attribute__((weak)) int find_write(void) { return 0; }
__attribute__((weak)) volatile uint64_t follow_enabled;
__attribute__((weak)) volatile uint64_t follow_pid;
__attribute__((weak)) int followed_slot(void) { return 0; }
__attribute__((weak)) volatile uint64_t fuxi_usb_append;
__attribute__((weak)) volatile uint64_t fuxi_usb_attempted;
__attribute__((weak)) int fuxi_usb_debug_start(void) { return 0; }
__attribute__((weak)) volatile uint64_t fuxi_usb_wait_channel;
__attribute__((weak)) volatile uint64_t g_kernel_kmod_info;
__attribute__((weak)) int geni_i2c_event(void) { return 0; }
__attribute__((weak)) int geni_i2c_poll(void) { return 0; }
__attribute__((weak)) int geni_i2c_prepare(void) { return 0; }
__attribute__((weak)) int geni_i2c_start_read(void) { return 0; }
__attribute__((weak)) int geni_i2c_start_read_bytes(void) { return 0; }
__attribute__((weak)) int geni_i2c_start_write(void) { return 0; }
__attribute__((weak)) int geni_i2c_start_write_bytes(void) { return 0; }
__attribute__((weak)) int geni_i2c_timeout(void) { return 0; }
__attribute__((weak)) int gpb_gmu_clocks_on(void) { return 0; }
__attribute__((weak)) int gpb_gmu_regs_readable(void) { return 0; }
__attribute__((weak)) int gpb_pll_configure(void) { return 0; }
__attribute__((weak)) int gpb_rcg_set(void) { return 0; }
__attribute__((weak)) int gpb_rd(void) { return 0; }
__attribute__((weak)) int gpb_read_gmu_clocks(void) { return 0; }
__attribute__((weak)) int gpb_run(void) { return 0; }
__attribute__((weak)) int gpb_set_bit0(void) { return 0; }
__attribute__((weak)) int gpb_state_text(void) { return 0; }
__attribute__((weak)) int image_matches(void) { return 0; }
__attribute__((weak)) volatile uint64_t lite_jobs;
__attribute__((weak)) volatile uint64_t live_arena;
__attribute__((weak)) int live_lifecycle(void) { return 0; }
__attribute__((weak)) volatile uint64_t live_state;
__attribute__((weak)) int lookup_peer(void) { return 0; }
__attribute__((weak)) volatile uint64_t max_mem;
__attribute__((weak)) int mmio_barrier(void) { return 0; }
__attribute__((weak)) int mmio_read(void) { return 0; }
__attribute__((weak)) int mmio_write(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_accelerator_status;
__attribute__((weak)) volatile uint64_t native_adreno_audit_attr;
__attribute__((weak)) volatile uint64_t native_adreno_audit_ticks;
__attribute__((weak)) volatile uint64_t native_adreno_cache_stats;
__attribute__((weak)) volatile uint64_t native_adreno_coherence;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_image;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_image_size;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_output_preserved;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_payload_bytes;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_pointer;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_records;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_refusal_mask;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_sha256;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_status;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_bit_refusals;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_input_preserved;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_output_preserved;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_packets;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_refusal_mask;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_status;
__attribute__((weak)) volatile uint64_t native_adreno_reassert_ticks;
__attribute__((weak)) volatile uint64_t native_adreno_wc_audit;
__attribute__((weak)) volatile uint64_t native_adreno_wc_distrusted;
__attribute__((weak)) volatile uint64_t native_constants_a_pointer;
__attribute__((weak)) volatile uint64_t native_constants_allocations_released;
__attribute__((weak)) volatile uint64_t native_constants_b_pointer;
__attribute__((weak)) volatile uint64_t native_constants_output_pointer;
__attribute__((weak)) volatile uint64_t native_constants_output_preserved;
__attribute__((weak)) volatile uint64_t native_constants_padded_bytes;
__attribute__((weak)) volatile uint64_t native_constants_physical;
__attribute__((weak)) volatile uint64_t native_constants_refusal_mask;
__attribute__((weak)) volatile uint64_t native_constants_status;
__attribute__((weak)) volatile uint64_t native_constants_written_bytes;
__attribute__((weak)) volatile uint64_t native_cpufreq_row;
__attribute__((weak)) volatile uint64_t native_cpufreq_stage;
__attribute__((weak)) volatile uint64_t native_data_persist_errors;
__attribute__((weak)) volatile uint64_t native_data_persist_first_lba;
__attribute__((weak)) volatile uint64_t native_data_persist_gpt;
__attribute__((weak)) volatile uint64_t native_data_persist_gpt_after;
__attribute__((weak)) volatile uint64_t native_data_persist_header;
__attribute__((weak)) volatile uint64_t native_data_persist_loaded;
__attribute__((weak)) volatile uint64_t native_data_persist_pages;
__attribute__((weak)) volatile uint64_t native_data_persist_present;
__attribute__((weak)) volatile uint64_t native_data_persist_state;
__attribute__((weak)) volatile uint64_t native_data_persist_syncs;
__attribute__((weak)) volatile uint64_t native_data_persist_writes;
__attribute__((weak)) volatile uint64_t native_gop_gpu_abandoned;
__attribute__((weak)) volatile uint64_t native_gop_gpu_completions;
__attribute__((weak)) volatile uint64_t native_gop_gpu_failures;
__attribute__((weak)) volatile uint64_t native_gop_gpu_offers;
__attribute__((weak)) volatile uint64_t native_gop_wait_stats;
__attribute__((weak)) volatile uint64_t native_gpu_coherence_row;
__attribute__((weak)) volatile uint64_t native_gpu_context;
__attribute__((weak)) volatile uint64_t native_gpu_cp;
__attribute__((weak)) volatile uint64_t native_gpu_dcvs;
__attribute__((weak)) volatile uint64_t native_gpu_gmu_clock_on;
__attribute__((weak)) volatile uint64_t native_gpu_gmu_clocks;
__attribute__((weak)) volatile uint64_t native_gpu_gmu_cold;
__attribute__((weak)) volatile uint64_t native_gpu_gmu_context;
__attribute__((weak)) volatile uint64_t native_gpu_gmu_state;
__attribute__((weak)) volatile uint64_t native_gpu_gx;
__attribute__((weak)) volatile uint64_t native_gpu_idle_sleeps;
__attribute__((weak)) volatile uint64_t native_gpu_idle_spins;
__attribute__((weak)) volatile uint64_t native_gpu_irq;
__attribute__((weak)) volatile uint64_t native_gpu_perf_vote;
__attribute__((weak)) volatile uint64_t native_gpu_power_result;
__attribute__((weak)) volatile uint64_t native_gpu_power_stage;
__attribute__((weak)) volatile uint64_t native_gpu_uc;
__attribute__((weak)) volatile uint64_t native_gpu_zap;
__attribute__((weak)) volatile uint64_t native_hid_class_sizes;
__attribute__((weak)) volatile uint64_t native_hid_input_command;
__attribute__((weak)) volatile uint64_t native_hid_input_events;
__attribute__((weak)) volatile uint64_t native_hid_input_meta_status;
__attribute__((weak)) volatile uint64_t native_hid_input_object;
__attribute__((weak)) volatile uint64_t native_hid_input_props;
__attribute__((weak)) volatile uint64_t native_hid_input_registry;
__attribute__((weak)) volatile uint64_t native_hid_input_results;
__attribute__((weak)) volatile uint64_t native_hid_load_status;
__attribute__((weak)) volatile uint64_t native_hid_matching_load_status;
__attribute__((weak)) volatile uint64_t native_keyevents_service;
__attribute__((weak)) volatile uint64_t native_keyevents_status;
__attribute__((weak)) volatile uint64_t native_keystore_class_size;
__attribute__((weak)) volatile uint64_t native_keystore_load_status;
__attribute__((weak)) volatile uint64_t native_keystore_service;
__attribute__((weak)) volatile uint64_t native_keystore_stage;
__attribute__((weak)) volatile uint64_t native_legacy_client_calls;
__attribute__((weak)) volatile uint64_t native_legacy_client_class;
__attribute__((weak)) int native_legacy_client_enter(void) { return 0; }
__attribute__((weak)) int native_legacy_client_observed(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_client_pid;
__attribute__((weak)) volatile uint64_t native_legacy_client_status;
__attribute__((weak)) volatile uint64_t native_legacy_client_type;
__attribute__((weak)) volatile uint64_t native_legacy_copy_bytes_last;
__attribute__((weak)) volatile uint64_t native_legacy_copy_bytes_sum;
__attribute__((weak)) volatile uint64_t native_legacy_copy_last;
__attribute__((weak)) volatile uint64_t native_legacy_copy_max;
__attribute__((weak)) volatile uint64_t native_legacy_copy_n;
__attribute__((weak)) volatile uint64_t native_legacy_copy_sum;
__attribute__((weak)) int native_legacy_copy_timing_observed(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_dt_attached;
__attribute__((weak)) volatile uint64_t native_legacy_frame_color_other;
__attribute__((weak)) int native_legacy_frame_colors_observed(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_frame_count;
__attribute__((weak)) volatile uint64_t native_legacy_frame_kind;
__attribute__((weak)) int native_legacy_frame_observed(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_frame_time;
__attribute__((weak)) volatile uint64_t native_legacy_gop_bytes;
__attribute__((weak)) volatile uint64_t native_legacy_gop_physical;
__attribute__((weak)) volatile uint64_t native_legacy_gop_virtual;
__attribute__((weak)) int native_legacy_gpu_fallback_observed(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_gpu_fallbacks;
__attribute__((weak)) volatile uint64_t native_legacy_gpu_last_status;
__attribute__((weak)) int native_legacy_gpu_offer(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_guard_slot;
__attribute__((weak)) volatile uint64_t native_legacy_meta_status;
__attribute__((weak)) volatile uint64_t native_legacy_pm_callbacks;
__attribute__((weak)) volatile uint64_t native_legacy_pm_calls;
__attribute__((weak)) int native_legacy_pm_observed(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_pm_stage;
__attribute__((weak)) volatile uint64_t native_legacy_pm_status;
__attribute__((weak)) volatile uint64_t native_legacy_prepare_attempts;
__attribute__((weak)) volatile uint64_t native_legacy_prepare_calls;
__attribute__((weak)) volatile uint64_t native_legacy_prepare_reason;
__attribute__((weak)) int native_legacy_prepare_scanout(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_prepare_wait_us;
__attribute__((weak)) volatile uint64_t native_legacy_properties;
__attribute__((weak)) int native_legacy_registration_observed(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_rej_class;
__attribute__((weak)) volatile uint64_t native_legacy_rej_options;
__attribute__((weak)) volatile uint64_t native_legacy_rej_reason;
__attribute__((weak)) volatile uint64_t native_legacy_rej_size;
__attribute__((weak)) volatile uint64_t native_legacy_rej_state;
__attribute__((weak)) volatile uint64_t native_legacy_rej_surface;
__attribute__((weak)) volatile uint64_t native_legacy_rej_surfaces;
__attribute__((weak)) volatile uint64_t native_legacy_retirement_calls;
__attribute__((weak)) volatile uint64_t native_legacy_stage;
__attribute__((weak)) volatile uint64_t native_legacy_surface_found;
__attribute__((weak)) int native_legacy_surface_rejected(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_surface_status;
__attribute__((weak)) volatile uint64_t native_legacy_swap_accepted_count;
__attribute__((weak)) volatile uint64_t native_legacy_swap_rejected_count;
__attribute__((weak)) volatile uint64_t native_legacy_swap_validation_calls;
__attribute__((weak)) int native_legacy_swap_validation_observed(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_legacy_swap_validation_reason;
__attribute__((weak)) volatile uint64_t native_legacy_swap_validation_result;
__attribute__((weak)) volatile uint64_t native_legacy_transfer_bytes;
__attribute__((weak)) volatile uint64_t native_legacy_transfer_calls;
__attribute__((weak)) volatile uint64_t native_legacy_unit_scale_status;
__attribute__((weak)) int native_legacy_vsync_observed(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_mobile_provider_client;
__attribute__((weak)) volatile uint64_t native_mobile_provider_dimensions;
__attribute__((weak)) volatile uint64_t native_mobile_provider_expected;
__attribute__((weak)) volatile uint64_t native_mobile_provider_meta_status;
__attribute__((weak)) volatile uint64_t native_mobile_provider_object;
__attribute__((weak)) volatile uint64_t native_mobile_provider_parent_match;
__attribute__((weak)) volatile uint64_t native_mobile_provider_query_status;
__attribute__((weak)) volatile uint64_t native_mobile_provider_released;
__attribute__((weak)) volatile uint64_t native_mobile_provider_stage;
__attribute__((weak)) volatile uint64_t native_original_client_status;
__attribute__((weak)) volatile uint64_t native_original_provider_factory_out_client;
__attribute__((weak)) volatile uint64_t native_original_provider_factory_result;
__attribute__((weak)) volatile uint64_t native_original_provider_frame;
__attribute__((weak)) volatile uint64_t native_original_provider_status;
__attribute__((weak)) volatile uint64_t native_ram_block_gpu_addon;
__attribute__((weak)) volatile uint64_t native_ram_block_volume_seed;
__attribute__((weak)) volatile uint64_t native_smmu4k_allocations_released;
__attribute__((weak)) volatile uint64_t native_smmu4k_cpu_mair;
__attribute__((weak)) volatile uint64_t native_smmu4k_data_physical;
__attribute__((weak)) volatile uint64_t native_smmu4k_data_pointer;
__attribute__((weak)) volatile uint64_t native_smmu4k_leaf_pages;
__attribute__((weak)) volatile uint64_t native_smmu4k_output_preserved;
__attribute__((weak)) volatile uint64_t native_smmu4k_pool_physical;
__attribute__((weak)) volatile uint64_t native_smmu4k_pool_pointer;
__attribute__((weak)) volatile uint64_t native_smmu4k_refusal_mask;
__attribute__((weak)) volatile uint64_t native_smmu4k_status;
__attribute__((weak)) volatile uint64_t native_smmu4k_table_pages;
__attribute__((weak)) volatile uint64_t native_touch_edge_stats;
__attribute__((weak)) volatile uint64_t native_touch_error;
__attribute__((weak)) volatile uint64_t native_touch_extent;
__attribute__((weak)) volatile uint64_t native_touch_last_x;
__attribute__((weak)) volatile uint64_t native_touch_loop_step;
__attribute__((weak)) volatile uint64_t native_touch_stroke_count;
__attribute__((weak)) volatile uint64_t native_ufs_block_failures;
__attribute__((weak)) volatile uint64_t native_ufs_block_reads;
__attribute__((weak)) volatile uint64_t native_ufs_blocks_published;
__attribute__((weak)) volatile uint64_t native_ufs_integrity_failures;
__attribute__((weak)) volatile uint64_t native_ufs_matched;
__attribute__((weak)) volatile uint64_t native_ufs_probe_calls;
__attribute__((weak)) volatile uint64_t native_ufs_read_ticks;
__attribute__((weak)) volatile uint64_t native_ufs_root_failure;
__attribute__((weak)) volatile uint64_t native_ufs_root_step;
__attribute__((weak)) volatile uint64_t native_ufs_verified_blocks;
__attribute__((weak)) volatile uint64_t native_ufs_verify_ticks;
__attribute__((weak)) int native_verified_root_probe(void) { return 0; }
__attribute__((weak)) int no_writes(void) { return 0; }
__attribute__((weak)) int now_ns(void) { return 0; }
__attribute__((weak)) int open_maps(void) { return 0; }
__attribute__((weak)) volatile uint64_t policy_head;
__attribute__((weak)) volatile uint64_t policy_tail;
__attribute__((weak)) volatile uint64_t policy_watchdogd;
__attribute__((weak)) int process_monitor(void) { return 0; }
__attribute__((weak)) int protocol_response(void) { return 0; }
__attribute__((weak)) int publish_live(void) { return 0; }
__attribute__((weak)) int pulse_monitor(void) { return 0; }
__attribute__((weak)) int px_text(void) { return 0; }
__attribute__((weak)) int read_reg(void) { return 0; }
__attribute__((weak)) int read_user(void) { return 0; }
__attribute__((weak)) volatile uint64_t reason_busy;
__attribute__((weak)) volatile uint64_t reason_chunk;
__attribute__((weak)) volatile uint64_t render_busy;
__attribute__((weak)) int reset_after_failure(void) { return 0; }
__attribute__((weak)) int reset_live(void) { return 0; }
__attribute__((weak)) int result_init(void) { return 0; }
__attribute__((weak)) volatile uint64_t sample_tid;
__attribute__((weak)) volatile uint64_t sheng_pmgr_observation;
__attribute__((weak)) volatile uint64_t sheng_watchdog_policy_status;
__attribute__((weak)) int smmu_bits(void) { return 0; }
__attribute__((weak)) int smmu_configure_bypass(void) { return 0; }
__attribute__((weak)) int smmu_plan_bypass(void) { return 0; }
__attribute__((weak)) int smmu_tests(void) { return 0; }
__attribute__((weak)) int start_live(void) { return 0; }
__attribute__((weak)) int startup_health(void) { return 0; }
__attribute__((weak)) int startup_now(void) { return 0; }
__attribute__((weak)) int startup_wait(void) { return 0; }
__attribute__((weak)) int table_read(void) { return 0; }
__attribute__((weak)) int tb_calc_rate(void) { return 0; }
__attribute__((weak)) int tb_choose_clock(void) { return 0; }
__attribute__((weak)) int tb_dfs_level_hz(void) { return 0; }
__attribute__((weak)) int test_sheng_command_db(void) { return 0; }
__attribute__((weak)) int test_sheng_votes(void) { return 0; }
__attribute__((weak)) int touch_fill(void) { return 0; }
__attribute__((weak)) int touch_monitor(void) { return 0; }
__attribute__((weak)) int touch_overlay(void) { return 0; }
__attribute__((weak)) int touch_overlay_locked(void) { return 0; }
__attribute__((weak)) volatile uint64_t trace_lock;
__attribute__((weak)) volatile uint64_t trace_slot;
__attribute__((weak)) int unmap_all(void) { return 0; }
__attribute__((weak)) volatile uint64_t vm_kernel_slide;
__attribute__((weak)) volatile uint64_t vm_page_free_count;
__attribute__((weak)) int wait_us(void) { return 0; }
__attribute__((weak)) int write_command(void) { return 0; }
__attribute__((weak)) int zero_result(void) { return 0; }
