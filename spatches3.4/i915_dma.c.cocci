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
identifier d;
@@
-struct drm_ioctl_desc d[] = {...};

@@
identifier d, e;
@@
- int d = DRM_ARRAY_SIZE(e);

@@
@@
-i915_write_hws_pga(...){...}
@@
@@
-i915_init_phys_hws(...){...}
@@
@@
-i915_kernel_lost_context(...){...}
@@
@@
-i915_initialize(...){...}
@@
@@
-i915_emit_cmds(...){...}
@@
@@
-ips_ping_for_i915_load(...){...}
@@
@@
-i915_quiescent(...){...}
@@
@@
-i915_setparam(...){...}
@@
@@
-i915_set_status_page(...){...}
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
-i915_stolen_to_phys(...){...}
@@
@@
-i915_setup_compression(...){...}
@@
@@
-i915_cleanup_compression(...){...}
@@
@@
-i915_switcheroo_set_state(...){...}
@@
@@
-i915_switcheroo_can_switch(...){...}
@@
@@
-i915_load_gem_init(...){...}
@@
@@
-i915_read_mch_val(...){...}
@@
@@
-i915_update_gfx_val(...){...}
@@
@@
-i915_master_destroy(...){...}
@@
@@
-i915_master_create(...){...}
@@
@@
-i915_vga_set_decode(...){...}
@@
identifier dev, d;
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
-if (dev->mm.d < E) {...}
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
identifier dev, d;
@@
-if (!dev->mm.d) {...}
@@
identifier dev;
@@
-dev->wq = ...;

@@
identifier dev;
expression E;
@@
-if (dev->wq == E) {...}
@@
identifier d, dev;
expression E;
@@
-d = dev->mm.gtt->gtt_mappable_entries << E;

@@
@@
-dma_set_coherent_mask(...);
@@
@@
-intel_setup_mchbar(...);
@@
@@
-if (! I915_NEED_GFX_HWS(...)){...}
@@
@@
-pci_enable_msi(...);
@@
@@
-acpi_video_register(...);
@@
identifier d;
@@
d = 
-drm_vblank_init(...);
+ 0;
@@
identifier d;
@@
d = 
-vga_client_register(...);
+0;
@@
@@
-intel_register_dsm_handler(...);
@@
identifier d;
@@
d = 
-vga_switcheroo_register_client(...);
+0;
@@
identifier d;
@@
d = 
-i915_load_gem_init(...);
+0;
@@
@@
-intel_modeset_gem_init(...);
@@
identifier d;
@@
d = 
-drm_irq_install(...);
+0;
@@
@@
-drm_kms_helper_poll_init(...);
@@
@@
-drm_irq_uninstall(...);
@@
@@
-i915_gem_cleanup_ringbuffer(...);
@@
@@
-i915_gem_cleanup_aliasing_ppgtt(...);
@@
@@
-vga_switcheroo_unregister_client(...);
@@
@@
-vga_client_register(...);
@@
@@
-io_mapping_free(...);
@@
@@
-pci_iounmap(...);
