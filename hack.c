struct drm_i915_gem_object *i915_gem_alloc_object(struct drm_device *dev,
						  size_t size)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_gem_object *obj;
	struct address_space *mapping;

	obj = allocz(sizeof(*obj));
	return obj;
}
