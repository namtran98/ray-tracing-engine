#include "world/World.hpp"
#include "utilities/Image.hpp"
#include <memory>
#include "samplers/Simple.hpp"
#include "tracers/Basic.hpp"
// #include "utilities/Mesh.hpp"

int main(int argc, char **argv) {
  World world;
  world.build();

  Sampler* sampler = world.sampler_ptr.get();
  ViewPlane& viewplane = world.vplane;
  Image image(viewplane);

  // Mesh mesher = Mesh((char*)"goldfish_low_res.ply");
  // SET TRACER HERE
  world.set_tracer(new Basic(&world));
  std::vector<Ray> rays;

  for (int x = 0; x < viewplane.hres; x++) {  // across.
    for (int y = 0; y < viewplane.vres; y++) {  // down.
      // Get rays for the pixel from the sampler. The pixel color is the
      // weighted sum of the shades for each ray.
      RGBColor pixel_color(0);
      rays = sampler->get_rays(x, y);
      int num_samples = rays.size();
      for (const auto& ray : rays) {
        pixel_color += (world.tracer_ptr->trace_ray(ray) / num_samples);
      }
      // Save color to image.
      image.set_pixel(x, y, pixel_color);
    }
  }
  // Write image to file.
  image.write_ppm("scene.ppm");

  return 0;
}
