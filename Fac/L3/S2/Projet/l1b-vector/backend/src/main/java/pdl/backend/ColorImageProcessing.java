package pdl.backend;
import boofcv.alg.color.ColorHsv;
import boofcv.struct.image.GrayF32;
import boofcv.struct.image.GrayU8;
import boofcv.struct.image.Planar;


public class ColorImageProcessing {
    // Color Level Processing
	public static void brightness(Planar<GrayU8> image, int delta) {
		for (int i=0; i<3; i++){ // Parcours les 3 niveaux de gris (rgb)
			brightness(image.getBand(i), delta);
		}
	}

	private static void brightness(GrayU8 input, int delta) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int gl = input.get(x, y)+delta;
				if (gl > 255) gl = 255;
                if (gl < 0) gl = 0;
				input.set(x, y, gl);
			}
		}
	}

    public static void meanFilter(Planar<GrayU8> input, Planar<GrayU8> output, int size) {
		for (int i=0; i<3; i++){
			meanFilter(input.getBand(i), output.getBand(i), size);
		}
	}

	private static void meanFilter(GrayU8 input, GrayU8 output, int size) {
		for (int y = 0; y < input.height; ++y) {
				for (int x = 0; x < input.width; ++x) {
			int nb = 0;
			long total = 0;
			int Yobjectif = y-(size/2);
			int Xobjectif = x-(size/2);
					for (int ybis = Yobjectif; ybis<Yobjectif+size; ybis++){
			  for (int xbis = Xobjectif; xbis<Xobjectif+size; xbis++){
				if (xbis>=0 && xbis<input.width && ybis>=0 && ybis<input.height){
				  nb++;
				  total = total + input.get(xbis, ybis);
				}
			  }
			}
			int bl = (int)(total/nb);
			output.set(x, y, bl);
				}
			}
	  }


	public static void colorToGray(Planar<GrayU8> input, GrayU8 output) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int r = input.getBand(0).get(x, y);
				int g = input.getBand(1).get(x, y);
				int b = input.getBand(2).get(x, y);
				int gl = (int)(0.3*r + 0.59*g + 0.11*b);  // Valeurs griser
				output.set(x, y, gl);
			}
		}
	}

	public static void colorFilter(Planar<GrayF32> input, double tint) {
		if (tint>359) tint = 359;
		if (tint<0) tint = 0;
		tint = Math.toRadians(tint);
		Planar<GrayF32> hsv = input.createSameShape();
		ColorHsv.rgbToHsv(input, hsv);
		for (int y = 0; y < hsv.height; ++y) {
			for (int x = 0; x < hsv.width; ++x) {
				hsv.getBand(0).set(x, y, (float)tint);
			}
		}
		ColorHsv.hsvToRgb(hsv, input);
	}



}
