@@
@@
-i915_batchbuffer(...){...}
@@
@@
-i915_chipset_val(...){...}
@@
@@
-i915_cleanup_compression(...){...}
@@
@@
-i915_cmdbuffer(...){...}
@@
@@
-i915_dispatch_batchbuffer(...){...}
@@
@@
-i915_dispatch_cmdbuffer(...){...}
@@
@@
-i915_dispatch_flip(...){...}
@@
@@
-i915_dma_cleanup(...){...}
@@
@@
-i915_dump_device_info(...){...}
@@
@@
-i915_dump_device_info(...);
@@
@@
-i915_dma_init(...){...}
@@
@@
-i915_dma_resume(...){...}
@@
@@
-i915_driver_device_is_agp(...){...}
@@
@@
-i915_driver_lastclose(...){...}
@@
@@
-i915_driver_open(...){...}
@@
@@
-i915_driver_postclose(...){...}
@@
@@
-i915_driver_preclose(...){...}
@@
@@
-i915_driver_unload(...){...}
@@
@@
-i915_emit_box(...){...}
@@
@@
-i915_emit_breadcrumb(...){...}
@@
@@
-i915_emit_cmds(...){...}
@@
@@
-i915_flip_bufs(...){...}
@@
@@
-i915_flush_ioctl(...){...}
@@
@@
-i915_free_hws(...){...}
@@
@@
-i915_getparam(...){...}
@@
@@
-i915_gfx_val(...){...}
@@
@@
-i915_gpu_busy(...){...}
@@
@@
-i915_gpu_lower(...){...}
@@
@@
-i915_gpu_raise(...){...}
@@
@@
-i915_gpu_turbo_disable(...){...}
@@
@@
-i915_init_phys_hws(...){...}
@@
@@
-i915_initialize(...){...}
@@
@@
-i915_kernel_lost_context(...){...}
@@
@@
-i915_load_gem_init(...){...}
@@
@@
-i915_master_create(...){...}
@@
@@
-i915_master_destroy(...){...}
@@
@@
-i915_mch_val(...){...}
@@
@@
-i915_quiescent(...){...}
@@
@@
-i915_read_mch_val(...){...}
@@
@@
-i915_set_status_page(...){...}
@@
@@
-i915_setparam(...){...}
@@
@@
-i915_setup_compression(...){...}
@@
@@
-i915_stolen_to_phys(...){...}
@@
@@
-i915_switcheroo_can_switch(...){...}
@@
@@
-i915_switcheroo_set_state(...){...}
@@
@@
-i915_update_gfx_val(...){...}
@@
@@
-i915_vga_set_decode(...){...}
@@
@@
-i915_warn_stolen(...){...}
@@
@@
-i915_write_hws_pga(...){...}
@@
@@
-intel_alloc_mchbar_resource(...){...}
@@
@@
-intel_setup_mchbar(...){...}
@@
@@
-intel_teardown_mchbar(...){...}
@@
@@
-ips_ping_for_i915_load(...){...}
@@
@@
-pvid_to_extvid(...){...}
@@
identifier d;
@@
-struct drm_ioctl_desc d[] = {...};
@@
identifier d;
@@
-struct vga_switcheroo_client_ops d = {...};
@@
expression E;
@@
-int i915_max_ioctl = E;
@@
@@
- struct cparams {...};
@@
@@
i915_driver_load(...){...
-drm_core_check_feature(...)
+ 1
...}
@@
@@
i915_driver_load(...){<...
-dma_set_coherent_mask(...)
...>}
@@
@@
i915_driver_load(...){<...
-pci_enable_msi(...)
+{extern int verbose; if (verbose) fprintf(stderr, "NOT setting enable MSI; fix me later\n");}
...>}
@@
@@
i915_driver_load(...){<...
-intel_opregion_init(...);
...>}
@@
@@
i915_driver_load(...){<...
-acpi_video_register(...);
...>}
@@
type T;
identifier f;
@@
T f(...){<...
(
-vga_client_register(...)
+ 0
|
-i915_load_gem_init(...)
+ 0
|
-drm_irq_install(...)
+ 0
)
...>}
@@
type T;
identifier f;
@@
T f(...){...
-vga_switcheroo_register_client(...)
+ 0
...}
@@
type T;
identifier f;
@@
T f(...){<...
(
-mutex_unlock(...);
|
-mutex_lock(...);
|
-drm_irq_install(...);
|
-drm_irq_uninstall(...);
|
-i915_gem_cleanup_ringbuffer(...);
|
-vga_switcheroo_unregister_client(...);
|
-vga_client_register(...);
|
-intel_register_dsm_handler(...);
|
-i915_load_gem_init(...);
|
-intel_modeset_gem_init(...);
|
-drm_irq_install(...);
|
-drm_kms_helper_poll_init(...);
)
...>}
@@
@@
-intel_read_legacy_status_page(...)
@@
@@
-i915_update_dri1_breadcrumb(...)
@@
@@
-i915_emit_irq(...){...}
@@
@@
-i915_wait_irq(...){...}
@@
@@
-i915_irq_wait(...){...}
@@
@@
-i915_mtrr_setup(...){...}
@@
@@
-i915_mtrr_setup(...);
@@
@@
-intel_read_legacy_status_page(...){...}
@@
@@
-i915_update_dri1_breadcrumb(...){...}
@@
@@
-i915_irq_emit(...){...}
@@
@@
-i915_vblank_pipe_get(...){...}
@@
@@
-i915_kick_out_firmware_fb(...){...}
@@
@@
-i915_kick_out_firmware_fb(...);
@@
@@
-i915_setup_sysfs(...);
@@
expression E;
@@
-aperture_size = E;
@@
identifier def, d;
expression E;
@@
-dev_priv->mm.d = E;
@@
identifier dev, d;
expression E;
@@
-if (dev->mm.d == E) {...}
@@
identifier dev, d;
expression E;
@@
-if (dev->mm.d >= E) {...}
@@
identifier dev, d, e;
expression E;
@@
-if (dev->mm.d.e) {...}
@@
identifier dev;
statement S;
@@
-if (dev->pdev->msi_enabled) S;
@@
identifier dev, d;
@@
-if (!dev->mm.d) {...}
@@
identifier dev, d, e;
statement S;
@@
-if (dev->mm.d.e) S;
@@
@@
-i915_init_phys_hws(...)
+0
@@
@@
-i915_gem_init_stolen(...)
+0
@@
@@
-i915_gem_init(...)
+0
@@
@@
-intel_gmch_probe(...)
+1
@@
@@
-drm_vblank_init(...)
+0
@@
@@
-intel_gpu_ips_init(...)
