// Copyright 2021, Aline Normoyle, alinen

#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   Image image;
   if (!image.load("../images/feep.png")) {
      std::cout << "ERROR: Cannot load image! Exiting...\n";
      exit(0);
   }

   for (int i = 0; i < image.height(); i++) {
      for (int j = 0; j < image.width(); j++) {
         Pixel c = image.get(i, j);
         std::cout << "(" << (int)c.r << "," << (int)c.g << "," << (int)c.b << ") ";
      }
      std::cout << std::endl;
   }
   image.save("feep-test-save.png"); // should match original
   
   // should print 4 4
   cout << "loaded feep: " << image.width() << " " << image.height() << endl;

   // test: copy constructor
   Image copy = image; 
   copy.save("feep-test-copy.png"); // should match original and load into gimp

   // test: assignment operator
   copy = image; 
   copy.save("feep-test-assignment.png"); // should match original and load into gimp

   // should print r,g,b
   Pixel pixel = image.get(1, 1);
   cout << (int) pixel.r << " " << (int) pixel.g << " " << (int) pixel.b << endl;

   // test: setting a color
   pixel.r = 255;
   image.set(1, 1, pixel);
   image.save("feep-test-newcolor.png");

   // test a non-trivial image
   if (!image.load("../images/earth.png")) {
      std::cout << "ERROR: Cannot load image! Exiting...\n";
      exit(0);
   }
   // should print 400 400
   cout << "loaded earth: " << image.width() << " " << image.height() << endl;

   // resize
   Image resize = image.resize(200,300);
   resize.save("zoro-200-300.png");

   // grayscale
   Image grayscale = image.grayscale(); 
   grayscale.save("zoro-grayscale.png");
   //blurrs the image I hope
   Image brr=image.brr();
   brr.save("zoro-brr.png");

   Image glitch=image.glitch();
   glitch.save("zoro-glitch.png");

   Image deepfry=image.deepfry(brr);
   deepfry.save("zoro-deepfry.png");

   Image crank90=image.crank90();
   crank90.save("zoro-crank90.png");

   Image lightest=image.lightest(crank90);
   lightest.save("zoro-lightest.png");

   Image darkest=image.darkest(crank90);
   darkest.save("zoro-darkest.png");

   Image difference=image.difference(crank90);
   difference.save("zoro-difference.png");

   Image multiply=image.multiply(crank90);
   multiply.save("zoro-multiply.png");

   Image glow=image.glow();
   glow.save("zoro-glow.png");
   // flip horizontal
   Image flip = image.flipVertical(); 
   flip.save("zoro-flip.png"); 

   // sub image
   Image sub = image.subimage(200, 200, 100, 100); 
   sub.save("zoro-subimage.png"); 

   // gamma correction
   Image gamma = image.gammaCorrect(0.6f); 
   gamma.save("zoro-gamma-0.6.png"); 

   gamma = image.gammaCorrect(2.2f);
   gamma.save("zoro-gamma-2.2.png"); 

   // alpha blend
   Image soup;
   soup.load("../images/soup.png");

   int y = (int) (0.5f * (image.width() - soup.width()));
   int x = (int) (0.5f * (image.height() - soup.height()));
   Image background = image.subimage(x, y, soup.width(), soup.height());
   background.save("background-test.png");
   Image blend = background.alphaBlend(soup, 0.5f);
   image.replace(blend, x, y);
   image.save("zoro-blend-0.5.png");
}

