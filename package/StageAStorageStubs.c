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

/* stage-A weak fallbacks for archives that are not built in this configuration */
__attribute__((weak)) volatile uint32_t native_legacy_stage;
__attribute__((weak)) volatile uint32_t native_legacy_swap_validation_calls;
__attribute__((weak)) volatile uint32_t native_legacy_swap_validation_result;
__attribute__((weak)) volatile uint32_t native_legacy_swap_validation_reason;
__attribute__((weak)) volatile uint32_t native_legacy_swap_accepted_count;
__attribute__((weak)) volatile uint32_t native_legacy_swap_rejected_count;
__attribute__((weak)) volatile uint32_t native_legacy_retirement_calls;
__attribute__((weak)) volatile uint32_t native_legacy_retired_generation;
__attribute__((weak)) volatile uint32_t native_legacy_presented_generation;
__attribute__((weak)) volatile uint32_t native_legacy_retired_frames;
__attribute__((weak)) volatile uint64_t native_legacy_transfer_calls;
__attribute__((weak)) volatile uint64_t native_legacy_transfer_bytes;
__attribute__((weak)) volatile uint32_t native_ram_block_gpu_addon;
__attribute__((weak)) volatile uint64_t native_ram_block_volume_seed;
__attribute__((weak)) volatile int native_verified_block_root_authorized;
__attribute__((weak)) volatile uint64_t native_verified_block_volume_device;
__attribute__((weak)) volatile unsigned char native_verified_block_manifest_sha384[48];

__attribute__((weak)) void fuxi_usb_debug_start(void) { }

__attribute__((weak)) volatile uint32_t native_legacy_pm_calls;
__attribute__((weak)) volatile uint32_t native_legacy_pm_stage;
__attribute__((weak)) volatile uint32_t native_legacy_prepare_attempts;
__attribute__((weak)) volatile uint32_t native_legacy_prepare_calls;
__attribute__((weak)) volatile uint32_t native_legacy_prepare_reason;
__attribute__((weak)) volatile uint32_t native_legacy_rej_class;
__attribute__((weak)) volatile uint32_t native_legacy_rej_reason;
__attribute__((weak)) volatile uint32_t native_legacy_rej_state;
__attribute__((weak)) volatile uint64_t native_legacy_rej_surface;
__attribute__((weak)) volatile uint32_t native_legacy_rej_size[2];
__attribute__((weak)) volatile uint64_t native_legacy_rej_surfaces[4];

/* exhaustive weak fallbacks generated from LegacyDisplayProbe.cpp */
__attribute__((weak)) volatile uint64_t native_gop_gpu_offer;
__attribute__((weak)) volatile uint64_t native_gop_presenter_create;
__attribute__((weak)) volatile uint64_t native_gop_presenter_set_source;
__attribute__((weak)) volatile uint64_t native_gop_presenter_static_init;
__attribute__((weak)) volatile uint64_t native_legacy_backend_guard;
__attribute__((weak)) volatile uint64_t native_legacy_chosen_rotation;
__attribute__((weak)) volatile uint64_t native_legacy_chosen_scale;
__attribute__((weak)) volatile uint64_t native_legacy_client_calls;
__attribute__((weak)) volatile uint64_t native_legacy_client_checkpoint;
__attribute__((weak)) volatile uint64_t native_legacy_client_class;
__attribute__((weak)) volatile uint64_t native_legacy_client_enter;
__attribute__((weak)) volatile uint64_t native_legacy_client_object;
__attribute__((weak)) volatile uint64_t native_legacy_client_observed;
__attribute__((weak)) volatile uint64_t native_legacy_client_pid;
__attribute__((weak)) volatile uint64_t native_legacy_client_status;
__attribute__((weak)) volatile uint64_t native_legacy_client_task;
__attribute__((weak)) volatile uint64_t native_legacy_client_type;
__attribute__((weak)) volatile uint64_t native_legacy_clients_dump;
__attribute__((weak)) volatile uint64_t native_legacy_copy_bytes_last;
__attribute__((weak)) volatile uint64_t native_legacy_copy_bytes_sum;
__attribute__((weak)) volatile uint64_t native_legacy_copy_last;
__attribute__((weak)) volatile uint64_t native_legacy_copy_max;
__attribute__((weak)) volatile uint64_t native_legacy_copy_n;
__attribute__((weak)) volatile uint64_t native_legacy_copy_sum;
__attribute__((weak)) volatile uint64_t native_legacy_copy_timing_observed;
__attribute__((weak)) volatile uint64_t native_legacy_display_allocate;
__attribute__((weak)) volatile uint64_t native_legacy_display_checkpoint;
__attribute__((weak)) volatile uint64_t native_legacy_display_static_init;
__attribute__((weak)) volatile uint64_t native_legacy_dt_attached;
__attribute__((weak)) volatile uint64_t native_legacy_frame_color_counts;
__attribute__((weak)) volatile uint64_t native_legacy_frame_color_other;
__attribute__((weak)) volatile uint64_t native_legacy_frame_colors;
__attribute__((weak)) volatile uint64_t native_legacy_frame_colors_observed;
__attribute__((weak)) volatile uint64_t native_legacy_frame_count;
__attribute__((weak)) volatile uint64_t native_legacy_frame_kind;
__attribute__((weak)) volatile uint64_t native_legacy_frame_observed;
__attribute__((weak)) volatile uint64_t native_legacy_frame_stats;
__attribute__((weak)) volatile uint64_t native_legacy_frame_time;
__attribute__((weak)) volatile uint64_t native_legacy_gop_bytes;
__attribute__((weak)) volatile uint64_t native_legacy_gop_height;
__attribute__((weak)) volatile uint64_t native_legacy_gop_map;
__attribute__((weak)) volatile uint64_t native_legacy_gop_mapping_checkpoint;
__attribute__((weak)) volatile uint64_t native_legacy_gop_mapping_observed;
__attribute__((weak)) volatile uint64_t native_legacy_gop_physical;
__attribute__((weak)) volatile uint64_t native_legacy_gop_virtual;
__attribute__((weak)) volatile uint64_t native_legacy_gop_width;
__attribute__((weak)) volatile uint64_t native_legacy_gpu_fallback_observed;
__attribute__((weak)) volatile uint64_t native_legacy_gpu_fallbacks;
__attribute__((weak)) volatile uint64_t native_legacy_gpu_last_status;
__attribute__((weak)) volatile uint64_t native_legacy_gpu_offer;
__attribute__((weak)) volatile uint64_t native_legacy_guard_caller;
__attribute__((weak)) volatile uint64_t native_legacy_guard_object;
__attribute__((weak)) volatile uint64_t native_legacy_guard_slot;
__attribute__((weak)) volatile uint64_t native_legacy_init_result;
__attribute__((weak)) volatile uint64_t native_legacy_meta_status;
__attribute__((weak)) volatile uint64_t native_legacy_nub;
__attribute__((weak)) volatile uint64_t native_legacy_object;
__attribute__((weak)) volatile uint64_t native_legacy_object_size;
__attribute__((weak)) volatile uint64_t native_legacy_parent_match;
__attribute__((weak)) volatile uint64_t native_legacy_pm_callbacks;
__attribute__((weak)) volatile uint64_t native_legacy_pm_observed;
__attribute__((weak)) volatile uint64_t native_legacy_pm_ordinal;
__attribute__((weak)) volatile uint64_t native_legacy_pm_status;
__attribute__((weak)) volatile uint64_t native_legacy_prepare_failures;
__attribute__((weak)) volatile uint64_t native_legacy_prepare_max_attempts;
__attribute__((weak)) volatile uint64_t native_legacy_prepare_report;
__attribute__((weak)) volatile uint64_t native_legacy_prepare_retried;
__attribute__((weak)) volatile uint64_t native_legacy_prepare_scanout;
__attribute__((weak)) volatile uint64_t native_legacy_prepare_wait_us;
__attribute__((weak)) volatile uint64_t native_legacy_probe_match;
__attribute__((weak)) volatile uint64_t native_legacy_properties;
__attribute__((weak)) volatile uint64_t native_legacy_properties_length;
__attribute__((weak)) volatile uint64_t native_legacy_properties_now;
__attribute__((weak)) volatile uint64_t native_legacy_registration_calls;
__attribute__((weak)) volatile uint64_t native_legacy_registration_observed;
__attribute__((weak)) volatile uint64_t native_legacy_rej_options;
__attribute__((weak)) volatile uint64_t native_legacy_rej_rects;
__attribute__((weak)) volatile uint64_t native_legacy_released;
__attribute__((weak)) volatile uint64_t native_legacy_retired_current;
__attribute__((weak)) volatile uint64_t native_legacy_retired_pending;
__attribute__((weak)) volatile uint64_t native_legacy_retirement_observed;
__attribute__((weak)) volatile uint64_t native_legacy_start_result;
__attribute__((weak)) volatile uint64_t native_legacy_state_words;
__attribute__((weak)) volatile uint64_t native_legacy_surface_found;
__attribute__((weak)) volatile uint64_t native_legacy_surface_rejected;
__attribute__((weak)) volatile uint64_t native_legacy_surface_status;
__attribute__((weak)) volatile uint64_t native_legacy_swap_request;
__attribute__((weak)) volatile uint64_t native_legacy_swap_surface;
__attribute__((weak)) volatile uint64_t native_legacy_swap_timeline;
__attribute__((weak)) volatile uint64_t native_legacy_swap_validation_checkpoint;
__attribute__((weak)) volatile uint64_t native_legacy_swap_validation_observed;
__attribute__((weak)) volatile uint64_t native_legacy_transfer_observed;
__attribute__((weak)) volatile uint64_t native_legacy_transfer_request;
__attribute__((weak)) volatile uint64_t native_legacy_unit_scale_calls;
__attribute__((weak)) volatile uint64_t native_legacy_unit_scale_status;
__attribute__((weak)) volatile uint64_t native_legacy_video_base;
__attribute__((weak)) volatile uint64_t native_legacy_video_bytes;
__attribute__((weak)) volatile uint64_t native_legacy_vsync_observed;
__attribute__((weak)) volatile uint64_t native_legacy_workloop;
__attribute__((weak)) volatile uint64_t native_touch_probe;
__attribute__((weak)) volatile uint64_t sheng_cpufreq_probe;

/* exhaustive weak fallbacks for every native_/sheng_ consumer symbol */
__attribute__((weak)) volatile uint64_t native_accelerator_allocated;
__attribute__((weak)) volatile uint64_t native_accelerator_attached;
int native_accelerator_checkpoint(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_accelerator_initialized;
__attribute__((weak)) volatile uint64_t native_accelerator_instances_after;
__attribute__((weak)) volatile uint64_t native_accelerator_instances_before;
__attribute__((weak)) volatile uint64_t native_accelerator_instances_live;
__attribute__((weak)) volatile uint64_t native_accelerator_object;
__attribute__((weak)) volatile uint64_t native_accelerator_parent;
__attribute__((weak)) volatile uint64_t native_accelerator_parent_match;
__attribute__((weak)) volatile uint64_t native_accelerator_released;
__attribute__((weak)) volatile uint64_t native_accelerator_size;
__attribute__((weak)) volatile uint64_t native_accelerator_stage;
int native_accelerator_static_init(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_accelerator_superclass;
__attribute__((weak)) volatile uint64_t native_accelerator_unrelated_match;
__attribute__((weak)) volatile uint64_t native_accelerator_vptr;
int native_adreno_accelerator_allocate(void) { return 0; }
int native_adreno_accelerator_instance_size(void) { return 0; }
int native_adreno_accelerator_static_init(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_adreno_asker_record;
int native_adreno_cached_read32(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_adreno_client_log;
__attribute__((weak)) volatile uint64_t native_adreno_client_record;
__attribute__((weak)) volatile uint64_t native_adreno_coherent_skips;
int native_adreno_dram_read32(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_adreno_export_stats;
__attribute__((weak)) volatile uint64_t native_adreno_fence_phys;
__attribute__((weak)) volatile uint64_t native_adreno_fence_wait;
int native_adreno_firmware_checkpoint(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_adreno_ib_log;
__attribute__((weak)) volatile uint64_t native_adreno_ib_log_count;
__attribute__((weak)) volatile uint64_t native_adreno_import_diag;
__attribute__((weak)) volatile uint64_t native_adreno_import_fail_offset;
__attribute__((weak)) volatile uint64_t native_adreno_import_fail_pa;
__attribute__((weak)) volatile uint64_t native_adreno_import_stage;
__attribute__((weak)) volatile uint64_t native_adreno_io_coherent;
__attribute__((weak)) volatile uint64_t native_adreno_line_audit;
__attribute__((weak)) volatile uint64_t native_adreno_map_fail;
__attribute__((weak)) volatile uint64_t native_adreno_metal_askers;
__attribute__((weak)) volatile uint64_t native_adreno_metal_diag;
__attribute__((weak)) volatile uint64_t native_adreno_metal_rows;
__attribute__((weak)) volatile uint64_t native_adreno_method_stats;
__attribute__((weak)) volatile uint64_t native_adreno_open_log;
__attribute__((weak)) volatile uint64_t native_adreno_open_log_count;
int native_adreno_pm4_checkpoint(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_adreno_pool_mib;
__attribute__((weak)) volatile uint64_t native_adreno_pool_stats;
__attribute__((weak)) volatile uint64_t native_adreno_pool_status;
__attribute__((weak)) volatile uint64_t native_adreno_pool_wc;
int native_adreno_publish(void) { return 0; }
int native_adreno_publish_stats(void) { return 0; }
int native_adreno_published_service(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_adreno_ring_log;
__attribute__((weak)) volatile uint64_t native_adreno_ring_log_count;
__attribute__((weak)) volatile uint64_t native_adreno_sqe_firmware_image;
__attribute__((weak)) volatile uint64_t native_adreno_sqe_firmware_image_size;
__attribute__((weak)) volatile uint64_t native_adreno_stall;
__attribute__((weak)) volatile uint64_t native_adreno_stall_mem;
__attribute__((weak)) volatile uint64_t native_adreno_trace_stage;
__attribute__((weak)) volatile uint64_t native_adreno_view_diag;
__attribute__((weak)) volatile uint64_t native_adreno_vm_phase_us;
__attribute__((weak)) volatile uint64_t native_adreno_wait_outer;
__attribute__((weak)) volatile uint64_t native_adreno_wc_enabled;
__attribute__((weak)) volatile uint64_t native_adreno_zap_image;
__attribute__((weak)) volatile uint64_t native_adreno_zap_image_size;
__attribute__((weak)) volatile uint64_t native_aks_calls;
__attribute__((weak)) volatile uint64_t native_aks_opens;
__attribute__((weak)) volatile uint64_t native_backlight_request;
int native_backlight_static_init(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_backlight_stats;
int native_constants_checkpoint(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_dpu_pipes;
__attribute__((weak)) volatile uint64_t native_dpu_stats;
int native_gop_handoff_call(void) { return 0; }
int native_gop_handoff_memory(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_gpu_addon2_stage;
__attribute__((weak)) volatile uint64_t native_gpu_addon2_status;
__attribute__((weak)) volatile uint64_t native_gpu_addon_stage;
__attribute__((weak)) volatile uint64_t native_gpu_addon_status;
int native_gpu_broker_checkpoint(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_gpu_broker_stage;
__attribute__((weak)) volatile uint64_t native_gpu_broker_status;
__attribute__((weak)) volatile uint64_t native_gpu_coherence;
__attribute__((weak)) volatile uint64_t native_gpu_zap_cost;
__attribute__((weak)) volatile uint64_t native_gpu_zap_free;
int native_hid_checkpoint(void) { return 0; }
int native_hid_input_allocate(void) { return 0; }
int native_hid_live_checkpoint(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_hid_resource_found;
__attribute__((weak)) volatile uint64_t native_hid_stage;
int native_hid_static_init(void) { return 0; }
int native_hid_touch_allocate(void) { return 0; }
int native_keyevents_allocate(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_keyevents_refused_opens;
__attribute__((weak)) volatile uint64_t native_keyevents_stage;
int native_keyevents_static_init(void) { return 0; }
int native_keystore_checkpoint(void) { return 0; }
int native_legacy_swap_stage(void) { return 0; }
int native_mobile_display_create(void) { return 0; }
int native_mobile_display_provider_checkpoint(void) { return 0; }
int native_mobile_display_static_init(void) { return 0; }
int native_offline_accelerator_allocate(void) { return 0; }
int native_offline_accelerator_instance_size(void) { return 0; }
int native_offline_accelerator_instances(void) { return 0; }
int native_offline_gpu_create(void) { return 0; }
int native_offline_gpu_publish(void) { return 0; }
int native_offline_gpu_static_init(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_original_client_allocated;
__attribute__((weak)) volatile uint64_t native_original_client_attached;
int native_original_client_checkpoint(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_original_client_initialized;
__attribute__((weak)) volatile uint64_t native_original_client_instances_after;
__attribute__((weak)) volatile uint64_t native_original_client_instances_before;
__attribute__((weak)) volatile uint64_t native_original_client_instances_live;
__attribute__((weak)) volatile uint64_t native_original_client_meta;
__attribute__((weak)) volatile uint64_t native_original_client_object;
__attribute__((weak)) volatile uint64_t native_original_client_parent;
__attribute__((weak)) volatile uint64_t native_original_client_parent_match;
__attribute__((weak)) volatile uint64_t native_original_client_parent_size;
__attribute__((weak)) volatile uint64_t native_original_client_provider_initialized;
__attribute__((weak)) volatile uint64_t native_original_client_released;
__attribute__((weak)) volatile uint64_t native_original_client_size;
__attribute__((weak)) volatile uint64_t native_original_client_stage;
__attribute__((weak)) volatile uint64_t native_original_client_unrelated_match;
__attribute__((weak)) volatile uint64_t native_original_client_vptr;
__attribute__((weak)) volatile uint64_t native_original_client_wrong_start;
int native_original_provider_allocate(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_original_provider_allocated;
__attribute__((weak)) volatile uint64_t native_original_provider_attached;
__attribute__((weak)) volatile uint64_t native_original_provider_backend;
__attribute__((weak)) volatile uint64_t native_original_provider_callback;
int native_original_provider_checkpoint(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_original_provider_client_instances_at_callback;
__attribute__((weak)) volatile uint64_t native_original_provider_client_instances_before;
__attribute__((weak)) volatile uint64_t native_original_provider_client_instances_live;
__attribute__((weak)) volatile uint64_t native_original_provider_client_type;
__attribute__((weak)) volatile uint64_t native_original_provider_descriptor_provisioned;
__attribute__((weak)) volatile uint64_t native_original_provider_descriptor_refused;
__attribute__((weak)) volatile uint64_t native_original_provider_factory_returned;
__attribute__((weak)) volatile uint64_t native_original_provider_initialized;
int native_original_provider_instances(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_original_provider_instances_after;
__attribute__((weak)) volatile uint64_t native_original_provider_instances_before;
__attribute__((weak)) volatile uint64_t native_original_provider_instances_live;
__attribute__((weak)) volatile uint64_t native_original_provider_object;
__attribute__((weak)) volatile uint64_t native_original_provider_parent;
__attribute__((weak)) volatile uint64_t native_original_provider_parent_match;
__attribute__((weak)) volatile uint64_t native_original_provider_registered;
__attribute__((weak)) volatile uint64_t native_original_provider_released;
int native_original_provider_required(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_original_provider_size;
__attribute__((weak)) volatile uint64_t native_original_provider_stage;
__attribute__((weak)) volatile uint64_t native_original_provider_start_result;
__attribute__((weak)) volatile uint64_t native_original_provider_start_returned;
int native_original_provider_static_init(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_original_provider_vptr;
int native_smmu4k_checkpoint(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_touch_contacts;
__attribute__((weak)) volatile uint64_t native_touch_firmware;
__attribute__((weak)) volatile uint64_t native_touch_firmware_size;
__attribute__((weak)) volatile uint64_t native_touch_frames;
__attribute__((weak)) volatile uint64_t native_touch_hid_reports;
__attribute__((weak)) volatile uint64_t native_touch_ids;
__attribute__((weak)) volatile uint64_t native_touch_irq_stats;
__attribute__((weak)) volatile uint64_t native_touch_last_y;
int native_touch_set_sink(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_touch_stage_done;
__attribute__((weak)) volatile uint64_t native_touch_step;
__attribute__((weak)) volatile uint64_t native_touch_strokes;
__attribute__((weak)) volatile uint64_t native_touch_trace;
__attribute__((weak)) volatile uint64_t native_touch_valid;
int native_ufs_dpu_map(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_ufs_dpu_state;
int native_ufs_export_blocks(void) { return 0; }
int native_ufs_export_write(void) { return 0; }
int native_ufs_log_open(void) { return 0; }
int native_ufs_log_sync(void) { return 0; }
int native_ufs_log_write(void) { return 0; }
int native_ufs_progress_text(void) { return 0; }
int native_ufs_store_gpt_check(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_wi_count;
__attribute__((weak)) volatile uint64_t native_wi_log;
int sheng_backlight_probe(void) { return 0; }
int sheng_backlight_start(void) { return 0; }
__attribute__((weak)) volatile uint64_t sheng_bcm_policy;
int sheng_dpu_probe(void) { return 0; }
__attribute__((weak)) volatile uint64_t sheng_gmu_firmware_sha256;
__attribute__((weak)) volatile uint64_t sheng_gmu_opps;
__attribute__((weak)) volatile uint64_t sheng_gmu_rsc_setup;
__attribute__((weak)) volatile uint64_t sheng_gmu_window_bytes;
__attribute__((weak)) volatile uint64_t sheng_gmu_window_physical;
__attribute__((weak)) volatile uint64_t sheng_gpu_bandwidths;
__attribute__((weak)) volatile uint64_t sheng_gpu_opps;
int sheng_gpu_power_probe(void) { return 0; }
__attribute__((weak)) volatile uint64_t sheng_gpu_smmu_sids;
int sheng_original_pmgr_nub_create(void) { return 0; }
int sheng_original_pmgr_nub_read(void) { return 0; }
int sheng_original_pmgr_nub_write(void) { return 0; }
int sheng_pmgr_checkpoint(void) { return 0; }
int sheng_pmgr_run(void) { return 0; }
int sheng_pmgr_static_init(void) { return 0; }
