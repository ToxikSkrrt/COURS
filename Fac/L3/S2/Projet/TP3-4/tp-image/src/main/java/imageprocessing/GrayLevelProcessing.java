package imageprocessing;

import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayU8;

public class GrayLevelProcessing {

	public static void threshold(GrayU8 input, int t) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int gl = input.get(x, y);
				if (gl < t) {
					gl = 0;
				} else {
					gl = 255;
				}
				input.set(x, y, gl);
			}
		}
	}

	public static void brightness(GrayU8 input, int delta) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int gl = input.get(x, y);
				int gl_out = gl + delta;
				if (gl_out > 255) {
					gl = 255;
				} else if (gl_out < 0) {
					gl = 0;
				} else {
					gl = gl_out;
				}
				input.set(x, y, gl);
			}
		}
	}

	public static int dynamic_calcul(int min, int max, int val) {
		return (255 / (max - min)) * (val - min);
	}

	public static void contrast_dynamic(GrayU8 input) {
		int min = 255, max = 0;
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int val = input.get(x, y);
				if (val < min)
					min = val;
				else if (val > max)
					max = val;
			}
		}
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int val = input.get(x, y);
				input.set(x, y, dynamic_calcul(min, max, val));
			}
		}
	}

	public static void contrast_dynamic_LUT(GrayU8 input) {
		int min = 255, max = 0;

		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int val = input.get(x, y);
				if (val < min)
					min = val;
				else if (val > max)
					max = val;
			}
		}

		int LUT[] = new int[256];
		for (int i = 0; i < 256; i++)
			LUT[i] = dynamic_calcul(min, max, i);

		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int val = input.get(x, y);
				input.set(x, y, LUT[val]);
			}
		}
	}

	public static void contrast_egalisation(GrayU8 input) {
		int cumul[] = new int[256], LUT[] = new int[256];
		int N = input.height * input.width;

		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int val = input.get(x, y);
				cumul[val]++;
			}
		}

		for (int i = 1; i < 256; i++) {
			cumul[i] += cumul[i - 1];
			LUT[i] = (cumul[i] * 255) / N;
		}

		LUT[0] = (cumul[0] * 255) / N;

		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int val = input.get(x, y);
				input.set(x, y, LUT[val]);
			}
		}
	}

	public static void main(String[] args) {

		// load image
		if (args.length < 2) {
			System.out.println("missing input or output image filename");
			System.exit(-1);
		}
		final String inputPath = args[0];
		GrayU8 input = UtilImageIO.loadImage(inputPath, GrayU8.class);
		if (input == null) {
			System.err.println("Cannot read input file '" + inputPath);
			System.exit(-1);
		}

		// processing

		// threshold(input, 128);
		// brightness(input, 50);
		// contrast_dynamic(input);
		// contrast_dynamic_LUT(input);
		contrast_egalisation(input);

		// save output image
		final String outputPath = args[1];
		UtilImageIO.saveImage(input, outputPath);
		System.out.println("Image saved in: " + outputPath);
	}

}