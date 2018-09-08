/*************************************************************************/
/*  rasterizer_storage_vulkan.h                                          */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2018 Cengiz Terzibas (Yaakuro)                     */
/* Copyright (c) 2014-2017 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef RASTERIZER_STORAGE_VULKAN_H
#define RASTERIZER_STORAGE_VULKAN_H

#include "servers/visual/rasterizer.h"
#include "servers/visual/shader_language.h"
#include "vulkan_framework.h"

class RasterizerCanvasVulkan;
class RasterizerSceneVulkan;
class RenderTarget;

class vkf::FrameBuffer;

struct Instantiable : public RID_Data {

	SelfList<RasterizerScene::InstanceBase>::List instance_list;

	_FORCE_INLINE_ void instance_change_notify() {

		SelfList<RasterizerScene::InstanceBase> *instances = instance_list.first();
		while (instances) {

			instances->self()->base_changed();
			instances = instances->next();
		}
	}

	_FORCE_INLINE_ void instance_material_change_notify() {

		SelfList<RasterizerScene::InstanceBase> *instances = instance_list.first();
		while (instances) {

			instances->self()->base_material_changed();
			instances = instances->next();
		}
	}

	_FORCE_INLINE_ void instance_remove_deps() {
		SelfList<RasterizerScene::InstanceBase> *instances = instance_list.first();
		while (instances) {

			SelfList<RasterizerScene::InstanceBase> *next = instances->next();
			instances->self()->base_removed();
			instances = next;
		}
	}

	Instantiable() {}
	virtual ~Instantiable() {
	}
};

class RasterizerStorageVulkan : public RasterizerStorage {
	public:

		enum RenderArchitecture {
			RENDER_ARCH_MOBILE,
			RENDER_ARCH_DESKTOP,
		};
	
		struct Config {
	
			bool shrink_textures_x2;
			bool use_fast_texture_filter;
			bool use_anisotropic_filter;
	
			bool s3tc_supported;
			bool latc_supported;
			bool rgtc_supported;
			bool bptc_supported;
			bool etc_supported;
			bool etc2_supported;
			bool pvrtc_supported;
	
			bool hdr_supported;
	
			bool srgb_decode_supported;
	
			bool use_rgba_2d_shadows;
	
			float anisotropic_level;
	
			int max_texture_image_units;
			int max_texture_size;
	
			bool generate_wireframes;
	
			bool use_texture_array_environment;
	
			Set<String> extensions;
	
			bool keep_original_textures;
	
			bool no_depth_prepass;
			bool force_vertex_shading;
		} config;

		struct Info {
			uint64_t texture_mem;
			uint64_t vertex_mem;
	
			struct Render {
				uint32_t object_count;
				uint32_t draw_call_count;
				uint32_t material_switch_count;
				uint32_t surface_switch_count;
				uint32_t shader_rebind_count;
				uint32_t vertices_count;
	
				void reset() {
					object_count = 0;
					draw_call_count = 0;
					material_switch_count = 0;
					surface_switch_count = 0;
					shader_rebind_count = 0;
					vertices_count = 0;
				}
			} render, render_final, snap;
	
			Info() {
	
				texture_mem = 0;
				vertex_mem = 0;
				render.reset();
				render_final.reset();
			}
	
		} info;

		void initialize();
		void finalize();

		struct GeometryOwner : public Instantiable {

			virtual ~GeometryOwner() {}
		};
		struct Geometry : Instantiable {

			enum Type {
				GEOMETRY_INVALID,
				GEOMETRY_SURFACE,
				GEOMETRY_IMMEDIATE,
				GEOMETRY_MULTISURFACE,
			};

			Type type;
			RID material;
			uint64_t last_pass;
			uint32_t index;

			virtual void material_changed_notify() {}

			Geometry() {
				last_pass = 0;
				index = 0;
			}
		};

		/* TEXTURE API */
		class Texture : public RID_Data {
			public:
			Texture *proxy;
			Set<Texture *> proxy_owners;

			bool active;
			uint32_t flags;
			String path;
			int width, height, depth;
			Image::Format format;
			vkf::Texture* vulkan_texture;
			vkf::TextureSampler* texture_sampler;
			RenderTarget *render_target;
			VS::TextureType type;

			VisualServer::TextureDetectCallback detect_3d;
			void *detect_3d_ud;
	
			VisualServer::TextureDetectCallback detect_srgb;
			void *detect_srgb_ud;
	
			VisualServer::TextureDetectCallback detect_normal;
			void *detect_normal_ud;
		};

		mutable RID_Owner<Texture> texture_owner;

		RID texture_create() override final;
		void texture_allocate(RID p_texture,
				int p_width,
				int p_height,
				int p_depth_3d,
				Image::Format p_format,
				VS::TextureType p_type,
				uint32_t p_flags = VS::TEXTURE_FLAGS_DEFAULT) override final;

		void texture_set_data(RID p_texture, const Ref<Image> &p_image, int p_level = 0) override final;

		void texture_set_data_partial(RID p_texture,
				const Ref<Image> &p_image,
				int src_x, int src_y,
				int src_w, int src_h,
				int dst_x, int dst_y,
				int p_dst_mip,
				int p_level = 0) override final;

		Ref<Image> texture_get_data(RID p_texture, int p_level = 0) const override final;
		void texture_set_flags(RID p_texture, uint32_t p_flags) override final;
		uint32_t texture_get_flags(RID p_texture) const override final;
		Image::Format texture_get_format(RID p_texture) const override final;
		VS::TextureType texture_get_type(RID p_texture) const override final;
		uint32_t texture_get_texid(RID p_texture) const override final;
		uint32_t texture_get_width(RID p_texture) const override final;
		uint32_t texture_get_height(RID p_texture) const override final;
		uint32_t texture_get_depth(RID p_texture) const override final;
		void texture_set_size_override(RID p_texture, int p_width, int p_height, int p_depth_3d) override final;

		void texture_set_path(RID p_texture, const String &p_path) override final;
		String texture_get_path(RID p_texture) const override final;

		void texture_set_shrink_all_x2_on_set_data(bool p_enable) override final;

		void texture_debug_usage(List<VS::TextureInfo> *r_info) override final;

		RID texture_create_radiance_cubemap(RID p_source, int p_resolution = -1) const override final;

		void texture_set_detect_3d_callback(RID p_texture, VisualServer::TextureDetectCallback p_callback, void *p_userdata) override final;
		void texture_set_detect_srgb_callback(RID p_texture, VisualServer::TextureDetectCallback p_callback, void *p_userdata) override final;
		void texture_set_detect_normal_callback(RID p_texture, VisualServer::TextureDetectCallback p_callback, void *p_userdata) override final;

		void textures_keep_original(bool p_enable) override final;

		void texture_set_proxy(RID p_texture, RID p_proxy) override final;
		void texture_set_force_redraw_if_visible(RID p_texture, bool p_enable) override final;

		/* SKY API */

		struct Sky : public RID_Data {
			RID panorama;
			uint32_t radiance;
			int radiance_size;
		};
	
		mutable RID_Owner<Sky> sky_owner;		

		RID sky_create() override final;
		void sky_set_texture(RID p_sky, RID p_panorama, int p_radiance_size) override final;

		/* SHADER API */
		struct Material;
		struct Shader : public RID_Data {
			RID self;

			VS::ShaderMode mode;
			vkf::ShaderModule* shader;
			String code;
			SelfList<Material>::List materials;

			Map<StringName, ShaderLanguage::ShaderNode::Uniform> uniforms;
			Vector<uint32_t> ubo_offsets;
			uint32_t ubo_size;

			uint32_t texture_count;

			uint32_t custom_code_id;
			uint32_t version;

			SelfList<Shader> dirty_list;

			Map<StringName, RID> default_textures;

			Vector<ShaderLanguage::DataType> texture_types;
			Vector<ShaderLanguage::ShaderNode::Uniform::Hint> texture_hints;

			bool valid;

			String path;

			struct CanvasItem {

				enum BlendMode {
					BLEND_MODE_MIX,
					BLEND_MODE_ADD,
					BLEND_MODE_SUB,
					BLEND_MODE_MUL,
					BLEND_MODE_PMALPHA,
					BLEND_MODE_DISABLED,
				};

				int blend_mode;

				enum LightMode {
					LIGHT_MODE_NORMAL,
					LIGHT_MODE_UNSHADED,
					LIGHT_MODE_LIGHT_ONLY
				};

				int light_mode;
				bool uses_screen_texture;
				bool uses_screen_uv;
				bool uses_time;

			} canvas_item;

			struct Spatial {

				enum BlendMode {
					BLEND_MODE_MIX,
					BLEND_MODE_ADD,
					BLEND_MODE_SUB,
					BLEND_MODE_MUL,
				};

				int blend_mode;

				enum DepthDrawMode {
					DEPTH_DRAW_OPAQUE,
					DEPTH_DRAW_ALWAYS,
					DEPTH_DRAW_NEVER,
					DEPTH_DRAW_ALPHA_PREPASS,
				};

				int depth_draw_mode;

				enum CullMode {
					CULL_MODE_FRONT,
					CULL_MODE_BACK,
					CULL_MODE_DISABLED,
				};

				int cull_mode;

				bool uses_alpha;
				bool uses_alpha_scissor;
				bool unshaded;
				bool no_depth_test;
				bool uses_vertex;
				bool uses_discard;
				bool uses_sss;
				bool uses_screen_texture;
				bool uses_depth_texture;
				bool uses_time;
				bool writes_modelview_or_projection;
				bool uses_vertex_lighting;
				bool uses_world_coordinates;

			} spatial;

			struct Particles {

			} particles;

			bool uses_vertex_time;
			bool uses_fragment_time;

			Shader() :
					dirty_list(this) {

				shader = NULL;
				ubo_size = 0;
				valid = false;
				custom_code_id = 0;
				version = 1;
			}
		};

		mutable RID_Owner<Shader> shader_owner;	
		mutable SelfList<Shader>::List _shader_dirty_list;
		void _shader_make_dirty(Shader *p_shader);

		RID shader_create() override final;

		void shader_set_code(RID p_shader, const String &p_code) override final;
		String shader_get_code(RID p_shader) const override final;
		void shader_get_param_list(RID p_shader, List<PropertyInfo> *p_param_list) const override final;

		void shader_set_default_texture_param(RID p_shader, const StringName &p_name, RID p_texture) override final;
		RID shader_get_default_texture_param(RID p_shader, const StringName &p_name) const override final;

		void update_dirty_shaders();

		/* COMMON MATERIAL API */
		struct Material : public RID_Data {

			Shader *shader;
		//GLuint ubo_id;
			uint32_t ubo_size;
			Map<StringName, Variant> params;
			SelfList<Material> list;
			SelfList<Material> dirty_list;
			Vector<bool> texture_is_3d;
			Vector<RID> textures;
			float line_width;
			int render_priority;

			RID next_pass;

			uint32_t index;
			uint64_t last_pass;

			Map<Geometry *, int> geometry_owners;
			Map<RasterizerScene::InstanceBase *, int> instance_owners;

			bool can_cast_shadow_cache;
			bool is_animated_cache;

			Material() :
					list(this),
					dirty_list(this) {
				can_cast_shadow_cache = false;
				is_animated_cache = false;
				shader = NULL;
				line_width = 1.0;
				//ubo_id = 0;
				ubo_size = 0;
				last_pass = 0;
				render_priority = 0;
			}
		};

		mutable RID_Owner<Material> material_owner;
		mutable SelfList<Material>::List _material_dirty_list;

		void update_dirty_materials();

		RID material_create() override final;

		void material_set_render_priority(RID p_material, int priority) override final;
		void material_set_shader(RID p_shader_material, RID p_shader) override final;
		RID material_get_shader(RID p_shader_material) const override final;

		void material_set_param(RID p_material, const StringName &p_param, const Variant &p_value) override final;
		Variant material_get_param(RID p_material, const StringName &p_param) const override final;

		void material_set_line_width(RID p_material, float p_width) override final;

		void material_set_next_pass(RID p_material, RID p_next_material) override final;

		bool material_is_animated(RID p_material) override final;
		bool material_casts_shadows(RID p_material) override final;

		void material_add_instance_owner(RID p_material, RasterizerScene::InstanceBase *p_instance) override final;
		void material_remove_instance_owner(RID p_material, RasterizerScene::InstanceBase *p_instance) override final;

		/* MESH API */
		struct MultiMesh;
		struct Surface;
		struct Mesh : public GeometryOwner {

		bool active;
		Vector<Surface *> surfaces;
		int blend_shape_count;
		VS::BlendShapeMode blend_shape_mode;
		AABB custom_aabb;
		mutable uint64_t last_pass;
		SelfList<MultiMesh>::List multimeshes;
		_FORCE_INLINE_ void update_multimeshes() {

			SelfList<MultiMesh> *mm = multimeshes.first();
			while (mm) {
				mm->self()->instance_material_change_notify();
				mm = mm->next();
			}
		}

		Mesh() {
			blend_shape_mode = VS::BLEND_SHAPE_MODE_NORMALIZED;
			blend_shape_count = 0;
			last_pass = 0;
			active = false;
		}
	};

	mutable RID_Owner<Mesh> mesh_owner;

		RID mesh_create() override final;

		void mesh_add_surface(RID p_mesh, uint32_t p_format, VS::PrimitiveType p_primitive, const PoolVector<uint8_t> &p_array, int p_vertex_count, const PoolVector<uint8_t> &p_index_array, int p_index_count, const AABB &p_aabb, const Vector<PoolVector<uint8_t> > &p_blend_shapes = Vector<PoolVector<uint8_t> >(), const Vector<AABB> &p_bone_aabbs = Vector<AABB>()) override final;

		void mesh_set_blend_shape_count(RID p_mesh, int p_amount) override final;
		int mesh_get_blend_shape_count(RID p_mesh) const override final;

		void mesh_set_blend_shape_mode(RID p_mesh, VS::BlendShapeMode p_mode) override final;
		VS::BlendShapeMode mesh_get_blend_shape_mode(RID p_mesh) const override final;

		void mesh_surface_update_region(RID p_mesh, int p_surface, int p_offset, const PoolVector<uint8_t> &p_data) override final;

		void mesh_surface_set_material(RID p_mesh, int p_surface, RID p_material) override final;
		RID mesh_surface_get_material(RID p_mesh, int p_surface) const override final;

		int mesh_surface_get_array_len(RID p_mesh, int p_surface) const override final;
		int mesh_surface_get_array_index_len(RID p_mesh, int p_surface) const override final;

		PoolVector<uint8_t> mesh_surface_get_array(RID p_mesh, int p_surface) const override final;
		PoolVector<uint8_t> mesh_surface_get_index_array(RID p_mesh, int p_surface) const override final;

		uint32_t mesh_surface_get_format(RID p_mesh, int p_surface) const override final;
		VS::PrimitiveType mesh_surface_get_primitive_type(RID p_mesh, int p_surface) const override final;

		AABB mesh_surface_get_aabb(RID p_mesh, int p_surface) const override final;
		Vector<PoolVector<uint8_t> > mesh_surface_get_blend_shapes(RID p_mesh, int p_surface) const override final;
		Vector<AABB> mesh_surface_get_skeleton_aabb(RID p_mesh, int p_surface) const override final;

		void mesh_remove_surface(RID p_mesh, int p_index) override final;
		int mesh_get_surface_count(RID p_mesh) const override final;

		void mesh_set_custom_aabb(RID p_mesh, const AABB &p_aabb) override final;
		AABB mesh_get_custom_aabb(RID p_mesh) const override final;

		AABB mesh_get_aabb(RID p_mesh, RID p_skeleton) const override final;
		void mesh_clear(RID p_mesh) override final;

		/* MULTIMESH API */
	/* MULTIMESH API */

	struct MultiMesh : public GeometryOwner {
		RID mesh;
		int size;
		VS::MultimeshTransformFormat transform_format;
		VS::MultimeshColorFormat color_format;
		VS::MultimeshCustomDataFormat custom_data_format;
		Vector<float> data;
		AABB aabb;
		SelfList<MultiMesh> update_list;
		SelfList<MultiMesh> mesh_list;
		//GLuint buffer;
		int visible_instances;

		int xform_floats;
		int color_floats;
		int custom_data_floats;

		bool dirty_aabb;
		bool dirty_data;

		MultiMesh() :
				update_list(this),
				mesh_list(this) {
			dirty_aabb = true;
			dirty_data = true;
			xform_floats = 0;
			color_floats = 0;
			custom_data_floats = 0;
			visible_instances = -1;
			size = 0;
		//	buffer = 0;
			transform_format = VS::MULTIMESH_TRANSFORM_2D;
			color_format = VS::MULTIMESH_COLOR_NONE;
			custom_data_format = VS::MULTIMESH_CUSTOM_DATA_NONE;
		}
	};

	mutable RID_Owner<MultiMesh> multimesh_owner;

	SelfList<MultiMesh>::List multimesh_update_list;
		void update_dirty_multimeshes();

		RID multimesh_create() override final;

		void multimesh_allocate(RID p_multimesh, int p_instances, VS::MultimeshTransformFormat p_transform_format, VS::MultimeshColorFormat p_color_format, VS::MultimeshCustomDataFormat p_data = VS::MULTIMESH_CUSTOM_DATA_NONE) override final;
		int multimesh_get_instance_count(RID p_multimesh) const override final;

		void multimesh_set_mesh(RID p_multimesh, RID p_mesh) override final;
		void multimesh_instance_set_transform(RID p_multimesh, int p_index, const Transform &p_transform) override final;
		void multimesh_instance_set_transform_2d(RID p_multimesh, int p_index, const Transform2D &p_transform) override final;
		void multimesh_instance_set_color(RID p_multimesh, int p_index, const Color &p_color) override final;
		void multimesh_instance_set_custom_data(RID p_multimesh, int p_index, const Color &p_color) override final;

		RID multimesh_get_mesh(RID p_multimesh) const override final;

		Transform multimesh_instance_get_transform(RID p_multimesh, int p_index) const override final;
		Transform2D multimesh_instance_get_transform_2d(RID p_multimesh, int p_index) const override final;
		Color multimesh_instance_get_color(RID p_multimesh, int p_index) const override final;
		Color multimesh_instance_get_custom_data(RID p_multimesh, int p_index) const override final;
		void multimesh_set_as_bulk_array(RID p_multimesh, const PoolVector<float> &p_array) override final;
		void multimesh_set_visible_instances(RID p_multimesh, int p_visible) override final;
		int multimesh_get_visible_instances(RID p_multimesh) const override final;

		AABB multimesh_get_aabb(RID p_multimesh) const override final;

		/* IMMEDIATE API */
		struct Immediate : public Geometry {

			struct Chunk {

				RID texture;
				VS::PrimitiveType primitive;
				Vector<Vector3> vertices;
				Vector<Vector3> normals;
				Vector<Plane> tangents;
				Vector<Color> colors;
				Vector<Vector2> uvs;
				Vector<Vector2> uvs2;
			};

			List<Chunk> chunks;
			bool building;
			int mask;
			AABB aabb;

			Immediate() {
				type = GEOMETRY_IMMEDIATE;
				building = false;
			}
		};
		Vector3 chunk_vertex;
		Vector3 chunk_normal;
		Plane chunk_tangent;
		Color chunk_color;
		Vector2 chunk_uv;
		Vector2 chunk_uv2;

		mutable RID_Owner<Immediate> immediate_owner;

		RID immediate_create() override final;
		void immediate_begin(RID p_immediate, VS::PrimitiveType p_rimitive, RID p_texture = RID()) override final;
		void immediate_vertex(RID p_immediate, const Vector3 &p_vertex) override final;
		void immediate_normal(RID p_immediate, const Vector3 &p_normal) override final;
		void immediate_tangent(RID p_immediate, const Plane &p_tangent) override final;
		void immediate_color(RID p_immediate, const Color &p_color) override final;
		void immediate_uv(RID p_immediate, const Vector2 &tex_uv) override final;
		void immediate_uv2(RID p_immediate, const Vector2 &tex_uv) override final;
		void immediate_end(RID p_immediate) override final;
		void immediate_clear(RID p_immediate) override final;
		void immediate_set_material(RID p_immediate, RID p_material) override final;
		RID immediate_get_material(RID p_immediate) const override final;
		AABB immediate_get_aabb(RID p_immediate) const override final;

		/* SKELETON API */
		struct Skeleton : RID_Data {
		bool use_2d;
		int size;
		Vector<float> skel_texture;
		//GLuint texture;
		SelfList<Skeleton> update_list;
		Set<RasterizerScene::InstanceBase *> instances; //instances using skeleton
		Transform2D base_transform_2d;

		Skeleton() :
				update_list(this) {
			size = 0;

			use_2d = false;
			//texture = 0;
		}
	};

	mutable RID_Owner<Skeleton> skeleton_owner;

	SelfList<Skeleton>::List skeleton_update_list;
		void update_dirty_skeletons();

		RID skeleton_create() override final;
		void skeleton_allocate(RID p_skeleton, int p_bones, bool p_2d_skeleton = false) override final;
		int skeleton_get_bone_count(RID p_skeleton) const override final;
		void skeleton_bone_set_transform(RID p_skeleton, int p_bone, const Transform &p_transform) override final;
		void skeleton_bone_set_transform_2d(RID p_skeleton, int p_bone, const Transform2D &p_transform) override final;
		Transform skeleton_bone_get_transform(RID p_skeleton, int p_bone) const override final;
		Transform2D skeleton_bone_get_transform_2d(RID p_skeleton, int p_bone) const override final;
		void skeleton_set_base_transform_2d(RID p_skeleton, const Transform2D &p_base_transform) override final;

		/* Light API */
		struct Light : Instantiable {
			VS::LightType type;
			float param[VS::LIGHT_PARAM_MAX];
			Color color;
			Color shadow_color;
			RID projector;
			bool shadow;
			bool negative;
			bool reverse_cull;
			uint32_t cull_mask;
			VS::LightOmniShadowMode omni_shadow_mode;
			VS::LightOmniShadowDetail omni_shadow_detail;
			VS::LightDirectionalShadowMode directional_shadow_mode;
			bool directional_blend_splits;
			uint64_t version;
		};

		mutable RID_Owner<Light> light_owner;

		RID light_create(VS::LightType p_type) override final;

		void light_set_reverse_cull_face_mode(RID, bool) override final;
		void light_set_color(RID p_light, const Color &p_color) override final;
		void light_set_param(RID p_light, VS::LightParam p_param, float p_value) override final;
		void light_set_shadow(RID p_light, bool p_enabled) override final;
		void light_set_shadow_color(RID p_light, const Color &p_color) override final;
		void light_set_projector(RID p_light, RID p_texture) override final;
		void light_set_negative(RID p_light, bool p_enable) override final;
		void light_set_cull_mask(RID p_light, uint32_t p_mask) override final;

		void light_omni_set_shadow_mode(RID p_light, VS::LightOmniShadowMode p_mode) override final;
		void light_omni_set_shadow_detail(RID p_light, VS::LightOmniShadowDetail p_detail) override final;

		void light_directional_set_shadow_mode(RID p_light, VS::LightDirectionalShadowMode p_mode) override final;
		void light_directional_set_blend_splits(RID p_light, bool p_enable) override final;
		bool light_directional_get_blend_splits(RID p_light) const override final;
		void light_directional_set_shadow_depth_range_mode(RID p_light, VS::LightDirectionalShadowDepthRangeMode p_range_mode) override final;
		VS::LightDirectionalShadowDepthRangeMode light_directional_get_shadow_depth_range_mode(RID p_light) const override final;
	
		VS::LightDirectionalShadowMode light_directional_get_shadow_mode(RID p_light) override final;
		VS::LightOmniShadowMode light_omni_get_shadow_mode(RID p_light) override final;

		bool light_has_shadow(RID p_light) const override final;

		VS::LightType light_get_type(RID p_light) const override final;
		AABB light_get_aabb(RID p_light) const override final;
		float light_get_param(RID p_light, VS::LightParam p_param) override final;
		Color light_get_color(RID p_light) override final;
		uint64_t light_get_version(RID p_light) const override final;

		/* PROBE API */

		struct ReflectionProbe : Instantiable {
			VS::ReflectionProbeUpdateMode update_mode;
			float intensity;
			Color interior_ambient;
			float interior_ambient_energy;
			float interior_ambient_probe_contrib;
			float max_distance;
			Vector3 extents;
			Vector3 origin_offset;
			bool interior;
			bool box_projection;
			bool enable_shadows;
			uint32_t cull_mask;
		};
			
		mutable RID_Owner<ReflectionProbe> reflection_probe_owner;

		RID reflection_probe_create() override final;

		void reflection_probe_set_update_mode(RID p_probe, VS::ReflectionProbeUpdateMode p_mode) override final;
		void reflection_probe_set_intensity(RID p_probe, float p_intensity) override final;
		void reflection_probe_set_interior_ambient(RID p_probe, const Color &p_ambient) override final;
		void reflection_probe_set_interior_ambient_energy(RID p_probe, float p_energy) override final;
		void reflection_probe_set_interior_ambient_probe_contribution(RID p_probe, float p_contrib) override final;
		void reflection_probe_set_max_distance(RID p_probe, float p_distance) override final;
		void reflection_probe_set_extents(RID p_probe, const Vector3 &p_extents) override final;
		void reflection_probe_set_origin_offset(RID p_probe, const Vector3 &p_offset) override final;
		void reflection_probe_set_as_interior(RID p_probe, bool p_enable) override final;
		void reflection_probe_set_enable_box_projection(RID p_probe, bool p_enable) override final;
		void reflection_probe_set_enable_shadows(RID p_probe, bool p_enable) override final;
		void reflection_probe_set_cull_mask(RID p_probe, uint32_t p_layers) override final;

		AABB reflection_probe_get_aabb(RID p_probe) const override final;
		VS::ReflectionProbeUpdateMode reflection_probe_get_update_mode(RID p_probe) const override final;
		uint32_t reflection_probe_get_cull_mask(RID p_probe) const override final;
		Vector3 reflection_probe_get_extents(RID p_probe) const override final;
		Vector3 reflection_probe_get_origin_offset(RID p_probe) const override final;
		float reflection_probe_get_origin_max_distance(RID p_probe) const override final;
		bool reflection_probe_renders_shadows(RID p_probe) const override final;

		void instance_add_skeleton(RID p_skeleton, RasterizerScene::InstanceBase *p_instance) override final;
		void instance_remove_skeleton(RID p_skeleton, RasterizerScene::InstanceBase *p_instance) override final;
	
		void instance_add_dependency(RID p_base, RasterizerScene::InstanceBase *p_instance) override final;
		void instance_remove_dependency(RID p_base, RasterizerScene::InstanceBase *p_instance) override final;

		/* GI PROBE API */

		struct GIProbe : public Instantiable {
			AABB bounds;
			Transform to_cell;
			float cell_size;
	
			int dynamic_range;
			float energy;
			float bias;
			float normal_bias;
			float propagation;
			bool interior;
			bool compress;
	
			uint32_t version;
	
			PoolVector<int> dynamic_data;
		};
			
		mutable RID_Owner<GIProbe> gi_probe_owner;

		RID gi_probe_create() override final;

		void gi_probe_set_bounds(RID p_probe, const AABB &p_bounds) override final;
		AABB gi_probe_get_bounds(RID p_probe) const override final;

		void gi_probe_set_cell_size(RID p_probe, float p_range) override final;
		float gi_probe_get_cell_size(RID p_probe) const override final;

		void gi_probe_set_to_cell_xform(RID p_probe, const Transform &p_xform) override final;
		Transform gi_probe_get_to_cell_xform(RID p_probe) const override final;

		void gi_probe_set_dynamic_data(RID p_probe, const PoolVector<int> &p_data) override final;
		PoolVector<int> gi_probe_get_dynamic_data(RID p_probe) const override final;

		void gi_probe_set_dynamic_range(RID p_probe, int p_range) override final;
		int gi_probe_get_dynamic_range(RID p_probe) const override final;

		void gi_probe_set_energy(RID p_probe, float p_range) override final;
		float gi_probe_get_energy(RID p_probe) const override final;

		void gi_probe_set_bias(RID p_probe, float p_range) override final;
		float gi_probe_get_bias(RID p_probe) const override final;

		void gi_probe_set_normal_bias(RID p_probe, float p_range) override final;
		float gi_probe_get_normal_bias(RID p_probe) const override final;

		void gi_probe_set_propagation(RID p_probe, float p_range) override final;
		float gi_probe_get_propagation(RID p_probe) const override final;

		void gi_probe_set_interior(RID p_probe, bool p_enable) override final;
		bool gi_probe_is_interior(RID p_probe) const override final;

		void gi_probe_set_compress(RID p_probe, bool p_enable) override final;
		bool gi_probe_is_compressed(RID p_probe) const override final;

		uint32_t gi_probe_get_version(RID p_probe) override final;

		struct GIProbeData : public RID_Data {
			int width;
			int height;
			int depth;
			int levels;
			//GLuint tex_id;
			GIProbeCompression compression;
	
			GIProbeData() {
			}
		};
	
		mutable RID_Owner<GIProbeData> gi_probe_data_owner;

		RasterizerStorage::GIProbeCompression gi_probe_get_dynamic_data_get_preferred_compression() const override final;
		RID gi_probe_dynamic_data_create(int p_width, int p_height, int p_depth, GIProbeCompression p_compression) override final;
		void gi_probe_dynamic_data_update(RID p_gi_probe_data, int p_depth_slice, int p_slice_count, int p_mipmap, const void *p_data) override final;


		/* LIGHTMAP CAPTURE */

		RID lightmap_capture_create() override final;
		void lightmap_capture_set_bounds(RID p_capture, const AABB &p_bounds) override final;
		AABB lightmap_capture_get_bounds(RID p_capture) const override final;
		void lightmap_capture_set_octree(RID p_capture, const PoolVector<uint8_t> &p_octree) override final;
		PoolVector<uint8_t> lightmap_capture_get_octree(RID p_capture) const override final;
		void lightmap_capture_set_octree_cell_transform(RID p_capture, const Transform &p_xform) override final;
		Transform lightmap_capture_get_octree_cell_transform(RID p_capture) const override final;
		void lightmap_capture_set_octree_cell_subdiv(RID p_capture, int p_subdiv) override final;
		int lightmap_capture_get_octree_cell_subdiv(RID p_capture) const override final;
		void lightmap_capture_set_energy(RID p_capture, float p_energy) override final;
		float lightmap_capture_get_energy(RID p_capture) const override final;
		const PoolVector<LightmapCaptureOctree> *lightmap_capture_get_octree_ptr(RID p_capture) const override final;


		/* PARTICLES */

		struct Particles : public RID_Data {
			bool inactive;
			float inactive_time;
			bool emitting;
			bool one_shot;
			int amount;
			float lifetime;
			float pre_process_time;
			float explosiveness;
			float randomness;
			bool restart_request;
			AABB custom_aabb;
			bool use_local_coords;
			RID process_material;
	
			VS::ParticlesDrawOrder draw_order;
	
			Vector<RID> draw_passes;
	
			// GLuint particle_buffers[2];
			// GLuint particle_vaos[2];
	
			// GLuint particle_buffer_histories[2];
			// GLuint particle_vao_histories[2];
			bool particle_valid_histories[2];
			bool histories_enabled;
	
			SelfList<Particles> particle_element;
	
			float phase;
			float prev_phase;
			uint64_t prev_ticks;
			uint32_t random_seed;
	
			uint32_t cycle_number;
	
			float speed_scale;
	
			int fixed_fps;
			bool fractional_delta;
			float frame_remainder;
	
			bool clear;
	
			Transform emission_transform;
	
			Particles()
				: particle_element(this) {
				cycle_number = 0;
				emitting = false;
				one_shot = false;
				amount = 0;
				lifetime = 1.0;
				pre_process_time = 0.0;
				explosiveness = 0.0;
				randomness = 0.0;
				use_local_coords = true;
				fixed_fps = 0;
				fractional_delta = false;
				frame_remainder = 0;
				histories_enabled = false;
				speed_scale = 1.0;
				random_seed = 0;
	
				restart_request = false;
	
				custom_aabb = AABB(Vector3(-4, -4, -4), Vector3(8, 8, 8));
	
				draw_order = VS::PARTICLES_DRAW_ORDER_INDEX;
				// particle_buffers[0] = 0;
				// particle_buffers[1] = 0;
	
				prev_ticks = 0;
	
				clear = true;
				inactive = true;
				inactive_time = false;
	
				// glGenBuffers(2, particle_buffers);
				// glGenVertexArrays(2, particle_vaos);
			}
	
			~Particles() {
	
				// glDeleteBuffers(2, particle_buffers);
				// glDeleteVertexArrays(2, particle_vaos);
				// if (histories_enabled) {
				// 	glDeleteBuffers(2, particle_buffer_histories);
				// 	glDeleteVertexArrays(2, particle_vao_histories);
				// }
			}
		};
	
		SelfList<Particles>::List particle_update_list;
		void update_particles();

		RID particles_create() override final;

		void particles_set_emitting(RID p_particles, bool p_emitting) override final;
		bool particles_get_emitting(RID p_particles) override final;
		void particles_set_amount(RID p_particles, int p_amount) override final;
		void particles_set_lifetime(RID p_particles, float p_lifetime) override final;
		void particles_set_one_shot(RID p_particles, bool p_one_shot) override final;
		void particles_set_pre_process_time(RID p_particles, float p_time) override final;
		void particles_set_explosiveness_ratio(RID p_particles, float p_ratio) override final;
		void particles_set_randomness_ratio(RID p_particles, float p_ratio) override final;
		void particles_set_custom_aabb(RID p_particles, const AABB &p_aabb) override final;
		void particles_set_speed_scale(RID p_particles, float p_scale) override final;
		void particles_set_use_local_coordinates(RID p_particles, bool p_enable) override final;
		void particles_set_process_material(RID p_particles, RID p_material) override final;
		void particles_set_fixed_fps(RID p_particles, int p_fps) override final;
		void particles_set_fractional_delta(RID p_particles, bool p_enable) override final;
		void particles_restart(RID p_particles) override final;

		void particles_set_draw_order(RID p_particles, VS::ParticlesDrawOrder p_order) override final;

		void particles_set_draw_passes(RID p_particles, int p_count) override final;
		void particles_set_draw_pass_mesh(RID p_particles, int p_pass, RID p_mesh) override final;

		void particles_request_process(RID p_particles) override final;
		AABB particles_get_current_aabb(RID p_particles) override final;
		AABB particles_get_aabb(RID p_particles) const override final;

		void particles_set_emission_transform(RID p_particles, const Transform &p_transform) override final;

		int particles_get_draw_passes(RID p_particles) const override final;
		RID particles_get_draw_pass_mesh(RID p_particles, int p_pass) const override final;

		/* RENDER TARGET */
		struct RenderTarget : public RID_Data {
			vkf::FrameBuffer* framebuffer;
	
			struct Buffers {
	
				bool active;
				bool effects_active;
				vkf::FrameBuffer fbo;
				vkf::Texture2D* depth;
				vkf::Texture2D* specular;
				vkf::Texture2D* diffuse;
				vkf::Texture2D* normal_rough;
				vkf::Texture2D* sss;
	
				vkf::Texture2D* effect_fbo;
				vkf::Texture2D* effect;
	
			} buffers;
	
			struct Effects {
	
				struct MipMaps {
	
					struct Size {
						vkf::FrameBuffer* fbo;
						int width;
						int height;
					};
	
					Vector<Size> sizes;
					int levels;
	
					MipMaps() {
						levels = 0;
					}
				};
	
				MipMaps mip_maps[2]; //first mipmap chain starts from full-screen
				//GLuint depth2; //depth for the second mipmap chain, in case of desiring upsampling
	
				struct SSAO {
					vkf::FrameBuffer* blur_fbo[2]; // blur fbo
					vkf::Texture2D* blur_red[2]; // 8 bits red buffer
	
					vkf::Texture2D* linear_depth;
	
					Vector<vkf::FrameBuffer*> depth_mipmap_fbos; //fbos for depth mipmapsla ver
	
					SSAO() {
						blur_fbo[0] = 0;
						blur_fbo[1] = 0;
						linear_depth = 0;
					}
				} ssao;
	
				Effects() {}
	
			} effects;
	
			struct Exposure {
				vkf::FrameBuffer* fbo;
				vkf::Texture2D* color;
	
				Exposure() { fbo = 0; }
			} exposure;
	
			uint64_t last_exposure_tick;
	
			int width, height;
	
			bool flags[RENDER_TARGET_FLAG_MAX];
	
			bool used_in_frame;
			VS::ViewportMSAA msaa;
	
			RID texture;
	
			// RenderTarget() {
	
			// 	msaa = VS::VIEWPORT_MSAA_DISABLED;
			// 	width = 0;
			// 	height = 0;
			// 	exposure.fbo = 0;
			// 	buffers.fbo = 0;
			// 	used_in_frame = false;
	
			// 	for (int i = 0; i < RENDER_TARGET_FLAG_MAX; i++) {
			// 		flags[i] = false;
			// 	}
			// 	flags[RENDER_TARGET_HDR] = true;
	
			// 	buffers.active = false;
			// 	buffers.effects_active = false;
	
			// 	last_exposure_tick = 0;
			// }
		};
	
		mutable RID_Owner<RenderTarget> render_target_owner;

		RID render_target_create() override final;
		void render_target_set_size(RID p_render_target, int p_width, int p_height) override final;
		RID render_target_get_texture(RID p_render_target) const override final;
		void render_target_set_flag(RID p_render_target, RenderTargetFlags p_flag, bool p_value) override final;
		bool render_target_was_used(RID p_render_target) override final;
		void render_target_clear_used(RID p_render_target) override final;
		void render_target_set_msaa(RID p_render_target, VS::ViewportMSAA p_msaa) override final;

		/* CANVAS SHADOW */
		struct CanvasLightShadow : public RID_Data {

			int size;
			int height;
		//	GLuint fbo;
		//	GLuint depth;
		//	GLuint distance; //for older devices
		};

		RID_Owner<CanvasLightShadow> canvas_light_shadow_owner;

		RID canvas_light_shadow_buffer_create(int p_width) override final;

		/* LIGHT SHADOW MAPPING */

		struct CanvasOccluder : public RID_Data {

			//GLuint array_id; // 0 means, unconfigured
			//GLuint vertex_id; // 0 means, unconfigured
			//GLuint index_id; // 0 means, unconfigured
			PoolVector<Vector2> lines;
			int len;
		};

		RID_Owner<CanvasOccluder> canvas_occluder_owner;

		RID canvas_light_occluder_create() override final;
		void canvas_light_occluder_set_polylines(RID p_occluder, const PoolVector<Vector2> &p_lines) override final;

		VS::InstanceType get_base_type(RID p_rid) const override final;
		bool free(RID p_rid) override final;

		bool has_os_feature(const String &p_feature) const override final;

		void update_dirty_resources() override final;

		void set_debug_generate_wireframes(bool p_generate) override final;

		void render_info_begin_capture() override final;
		void render_info_end_capture() override final;
		int get_captured_render_info(VS::RenderInfo p_info) override final;

		int get_render_info(VS::RenderInfo p_info) override final;

		static RasterizerStorageVulkan *base_singleton;
		RasterizerStorageVulkan();
		~RasterizerStorageVulkan();

		RasterizerCanvasVulkan* canvas;
		RasterizerSceneVulkan* scene;
};

#endif
