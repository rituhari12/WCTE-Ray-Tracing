//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "camera.h"
#include "constant_medium.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"
#include "sphere.h"
#include "wcte_geometry.h"

int main() {
    hittable_list world;
    hittable_list lights;
    auto m = shared_ptr<material>();
    lights.add(make_shared<quad>(point3(343,554,332), vec3(-130,0,0), vec3(0,0,-105), m));
    lights.add(make_shared<sphere>(point3(190, 90, 190), 90, m));


    
    WCTEGeometry geom("wcte_geometry_file.json");

    // get geometry
    float mpmt_ro = geom.get_float("ro");
    float mpmt_ri = geom.get_float("ri");
    float mpmt_rmatrix = geom.get_float("rmatrix");
    float mpmt_rpmt = geom.get_float("rpmt");
    std::cerr<<"mpmt_ro="<<mpmt_ro<<std::endl;
    std::cerr<<"mpmt_ri="<<mpmt_ri<<std::endl;
    std::vector<float> dome_x = geom.get_vector("dome_x");
    std::vector<float> dome_y = geom.get_vector("dome_y");
    std::vector<float> dome_z = geom.get_vector("dome_z");
    std::vector<float> dome_ux = geom.get_vector("dome_ux");
    std::vector<float> dome_uy = geom.get_vector("dome_uy");
    std::vector<float> dome_uz = geom.get_vector("dome_uz");
    std::vector<float> dome_wx = geom.get_vector("dome_wx");
    std::vector<float> dome_wy = geom.get_vector("dome_wy");
    std::vector<float> dome_wz = geom.get_vector("dome_wz");
    unsigned nmpmt = dome_x.size();
    std::cerr<<"nMPMTs = "<< nmpmt <<std::endl;
    std::vector<float> blacks_x = geom.get_vector("blacks_x");
    std::vector<float> blacks_y = geom.get_vector("blacks_y");
    std::vector<float> blacks_z = geom.get_vector("blacks_z");
    std::vector<float> pmt_x = geom.get_vector("pmt_x");
    std::vector<float> pmt_y = geom.get_vector("pmt_y");
    std::vector<float> pmt_z = geom.get_vector("pmt_z");
    std::vector<float> pmt_dirx = geom.get_vector("pmt_dirx");
    std::vector<float> pmt_diry = geom.get_vector("pmt_diry");
    std::vector<float> pmt_dirz = geom.get_vector("pmt_dirz");
    std::cerr<<"nPMTs = "<<pmt_x.size()<<std::endl;
    unsigned npmts_per_mpmt = unsigned( pmt_x.size()/dome_x.size() );
    std::cerr<<"n PMT/ MPMT = "<<npmts_per_mpmt<<std::endl;
    std::vector<float> cam_x = geom.get_vector("cam_x");
    std::vector<float> cam_y = geom.get_vector("cam_y");
    std::vector<float> cam_z = geom.get_vector("cam_z");
    std::vector<float> cam_dirx = geom.get_vector("cam_dirx");
    std::vector<float> cam_diry = geom.get_vector("cam_diry");
    std::vector<float> cam_dirz = geom.get_vector("cam_dirz");
    std::cerr<<"n cameras = "<<cam_x.size()<<std::endl;
    std::vector<float> led_x = geom.get_vector("led_x");
    std::vector<float> led_y = geom.get_vector("led_y");
    std::vector<float> led_z = geom.get_vector("led_z");
    std::vector<float> led_dirx = geom.get_vector("led_ux");
    std::vector<float> led_diry = geom.get_vector("led_uy");
    std::vector<float> led_dirz = geom.get_vector("led_uz");
    std::vector<float> led_wx = geom.get_vector("led_wx");
    std::vector<float> led_wy = geom.get_vector("led_wy");
    std::vector<float> led_wz = geom.get_vector("led_wz");
    std::cerr<<"n LEDs = "<<led_x.size()<<std::endl;
    unsigned nled_per_mpmt = led_x.size() / nmpmt;
    
    
    
    //std::cout<<"ro="<<geom.get_float("ro")<<std::endl;
    //std::cout<<"ri="<<geom.get_float("ri")<<std::endl;
    auto air = make_shared<dielectric>(1.000293);
    auto water = make_shared<dielectric>(1.333);
    auto acrylic = make_shared<dielectric>(1.5);
    auto pmt_gold = make_shared<metal>( color(0.8,0.6,0.2) , 0.1 );
    auto blacksheet = make_shared<lambertian>( color(0.1,0.1,0.1) );
    auto blueled = make_shared<diffuse_light>( color(0.,0.,15.) );
    
    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    nmpmt=3; // for now look at one mpmt
    const float led_radius = 0.003; // meters
    const float radial_dist_innerdome_to_matrix = 0.03;
    float blacksheet_size = mpmt_ri*2.1;
    unsigned impmt_with_leds_on = 40;
    for ( unsigned impmt=0; impmt<nmpmt; impmt++ ){
      //if ( impmt == impmt_with_leds_on ){
          for ( unsigned iled=3+impmt*nled_per_mpmt; iled<(impmt+1)*nled_per_mpmt; iled++ ){
        	world.add( make_shared<sphere>( point3( led_x[iled], led_y[iled], led_z[iled]  ), led_radius, light ) ) ;
          }
      //}
      for ( unsigned ipmt=0; ipmt<npmts_per_mpmt; ipmt++ ){
    	unsigned cur_pmt = impmt*npmts_per_mpmt + ipmt;
   	world.add( make_shared<sphere>( point3( pmt_x[cur_pmt], pmt_y[cur_pmt], pmt_z[cur_pmt] ), mpmt_rpmt, pmt_gold ) );
      }
     world.add( make_shared<sphere>( point3( dome_x[impmt], dome_y[impmt], dome_z[impmt] ), mpmt_ro, acrylic ) );  // acrylic dome
     world.add( make_shared<sphere>( point3( dome_x[impmt], dome_y[impmt], dome_z[impmt] ), mpmt_ri, air ) );      // air inside acrylic dome
     //world.add( make_shared<sphere>( point3( dome_x[impmt], dome_y[impmt], dome_z[impmt] ), 
             //(mpmt_ri - radial_dist_innerdome_to_matrix), 
             //green ) ); // pmt matrix inside dome
      world.add( make_shared<sphere>( point3( dome_x[impmt], dome_y[impmt], dome_z[impmt] ),(mpmt_ri - radial_dist_innerdome_to_matrix)  , blacksheet));
     
      point3 bs_center = point3( blacks_x[impmt], blacks_y[impmt], blacks_z[impmt] );
      point3 bs_u = point3( dome_ux[impmt], dome_uy[impmt], dome_uz[impmt] );  
      point3 bs_w = point3( dome_wx[impmt], dome_wy[impmt], dome_wz[impmt] );
      point3 bs_v = cross( bs_w, bs_u );
      point3 tmp = bs_v;
      bs_v = bs_w;
      bs_w = bs_u;
      bs_u = tmp;
      point3 Qblacksheet = bs_center - 0.5*blacksheet_size*bs_u - 0.5*blacksheet_size*bs_v;
      world.add( make_shared<quad>( Qblacksheet, blacksheet_size*bs_u, blacksheet_size*bs_v, blacksheet ) );
    }
    
    
    camera cam;

    unsigned icamera = 5;
    cam.aspect_ratio      = 1.5;//1.5;
    cam.image_width       = 6336;//6336;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = color(0.01,0.01,0.01);

    cam.vfov     = 147;
    cam.lookfrom = point3( cam_x[icamera] , cam_y[icamera], cam_z[icamera]);
    cam.lookat   = point3( cam_dirx[icamera], cam_diry[icamera], cam_dirz[icamera] );
    cam.vup      = vec3(0, 1, 0); //???

    cam.defocus_angle = 0;

    cam.render(world, lights);
}
