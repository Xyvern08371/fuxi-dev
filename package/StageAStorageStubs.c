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
int native_accelerator_probe(void) { return 0; }
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
int native_adreno_firmware_probe(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_adreno_firmware_records;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_refusal_mask;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_sha256;
__attribute__((weak)) volatile uint64_t native_adreno_firmware_status;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_bit_refusals;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_input_preserved;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_output_preserved;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_packets;
int native_adreno_pm4_probe(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_adreno_pm4_refusal_mask;
__attribute__((weak)) volatile uint64_t native_adreno_pm4_status;
__attribute__((weak)) volatile uint64_t native_adreno_reassert_ticks;
__attribute__((weak)) volatile uint64_t native_adreno_wc_audit;
__attribute__((weak)) volatile uint64_t native_adreno_wc_distrusted;
int native_aks_call(void) { return 0; }
int native_aks_lock_state(void) { return 0; }
int native_aks_opened(void) { return 0; }
int native_aks_state_enabled(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_constants_a_pointer;
__attribute__((weak)) volatile uint64_t native_constants_allocations_released;
__attribute__((weak)) volatile uint64_t native_constants_b_pointer;
__attribute__((weak)) volatile uint64_t native_constants_output_pointer;
__attribute__((weak)) volatile uint64_t native_constants_output_preserved;
__attribute__((weak)) volatile uint64_t native_constants_padded_bytes;
__attribute__((weak)) volatile uint64_t native_constants_physical;
int native_constants_probe(void) { return 0; }
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
int native_hid_input_observed(void) { return 0; }
int native_hid_input_probe(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_hid_input_props;
__attribute__((weak)) volatile uint64_t native_hid_input_registry;
int native_hid_input_requested(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_hid_input_results;
__attribute__((weak)) volatile uint64_t native_hid_load_status;
__attribute__((weak)) volatile uint64_t native_hid_matching_load_status;
int native_keyevents_open_refused(void) { return 0; }
int native_keyevents_probe(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_keyevents_service;
__attribute__((weak)) volatile uint64_t native_keyevents_status;
__attribute__((weak)) volatile uint64_t native_keystore_class_size;
__attribute__((weak)) volatile uint64_t native_keystore_load_status;
int native_keystore_probe(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_keystore_service;
__attribute__((weak)) volatile uint64_t native_keystore_stage;
int native_legacy_display_late_probe(void) { return 0; }
int native_legacy_display_probe(void) { return 0; }
int native_metal_runtime_diagnostic(void) { return 0; }
int native_mobile_display_provider_probe(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_mobile_provider_client;
__attribute__((weak)) volatile uint64_t native_mobile_provider_dimensions;
__attribute__((weak)) volatile uint64_t native_mobile_provider_expected;
__attribute__((weak)) volatile uint64_t native_mobile_provider_meta_status;
__attribute__((weak)) volatile uint64_t native_mobile_provider_object;
__attribute__((weak)) volatile uint64_t native_mobile_provider_parent_match;
__attribute__((weak)) volatile uint64_t native_mobile_provider_query_status;
__attribute__((weak)) volatile uint64_t native_mobile_provider_released;
__attribute__((weak)) volatile uint64_t native_mobile_provider_stage;
int native_original_client_probe(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_original_client_status;
int native_original_provider_descriptor(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_original_provider_factory_out_client;
__attribute__((weak)) volatile uint64_t native_original_provider_factory_result;
__attribute__((weak)) volatile uint64_t native_original_provider_frame;
int native_original_provider_probe(void) { return 0; }
__attribute__((weak)) volatile uint64_t native_original_provider_status;
__attribute__((weak)) volatile uint64_t native_smmu4k_allocations_released;
__attribute__((weak)) volatile uint64_t native_smmu4k_cpu_mair;
__attribute__((weak)) volatile uint64_t native_smmu4k_data_physical;
__attribute__((weak)) volatile uint64_t native_smmu4k_data_pointer;
__attribute__((weak)) volatile uint64_t native_smmu4k_leaf_pages;
__attribute__((weak)) volatile uint64_t native_smmu4k_output_preserved;
__attribute__((weak)) volatile uint64_t native_smmu4k_pool_physical;
__attribute__((weak)) volatile uint64_t native_smmu4k_pool_pointer;
int native_smmu4k_probe(void) { return 0; }
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
int sheng_boot_setup_reset(void) { return 0; }
int sheng_boot_watchdog_policy(void) { return 0; }
__attribute__((weak)) volatile uint64_t sheng_pmgr_observation;
__attribute__((weak)) volatile uint64_t sheng_watchdog_policy_status;

/* generic fallbacks: every global the package defines, minus the two linked files */
__attribute__((weak)) volatile uint64_t boot_ui_trace_rows;
__attribute__((weak)) volatile uint64_t fuxi_usb_append;
__attribute__((weak)) volatile uint64_t fuxi_usb_debug_start;
__attribute__((weak)) volatile uint64_t native_verified_block_manifest_sha384;
__attribute__((weak)) volatile uint64_t native_verified_block_root_authorized;
__attribute__((weak)) volatile uint64_t native_verified_root_probe;

/* overlay trace globals only declared as extern */
__attribute__((weak)) volatile uint64_t boot_ui_trace_index;
__attribute__((weak)) volatile uint64_t boot_ui_trace_label;
__attribute__((weak)) volatile uint64_t boot_ui_trace_phase;
__attribute__((weak)) volatile uint64_t boot_ui_trace_ready;
__attribute__((weak)) volatile uint64_t boot_ui_trace_role_rows;
__attribute__((weak)) volatile uint64_t boot_ui_trace_snapshot;
