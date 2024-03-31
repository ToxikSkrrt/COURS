package imageprocessing;

import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayF32;
import boofcv.struct.image.GrayU8;
import boofcv.alg.color.ColorHsv;
import boofcv.core.image.ConvertImage;
import boofcv.io.image.ConvertBufferedImage;
import boofcv.struct.image.Planar;
import java.awt.image.BufferedImage;

public class ColorProcessing {

	public static void brightness(Planar<GrayU8> input, Planar<GrayU8> output, int delta) {
		for (int nbB = 0; nbB < input.getNumBands(); nbB++) {
			for (int y = 0; y < input.height; ++y) {
				for (int x = 0; x < input.width; ++x) {
					int rgb = input.getBand(nbB).get(x, y);
					int rgb_out = rgb + delta;
					if (rgb_out > 255) {
						rgb = 255;
					} else if (rgb_out < 0) {
						rgb = 0;
					} else {
						rgb = rgb_out;
					}
					output.getBand(nbB).set(x, y, rgb);
				}
			}
		}
	}

	public static void meanFilter(Planar<GrayU8> input, Planar<GrayU8> output, int size) {
		for (int nbB = 0; nbB < input.getNumBands(); nbB++) {
			for (int y = size / 2; y < input.height - (size / 2); ++y) {
				for (int x = size / 2; x < input.width - (size / 2); ++x) {
					int sum = 0;
					for (int j = -size / 2; j <= size / 2; j++) {
						for (int i = -size / 2; i <= size / 2; i++) {
							sum += input.getBand(nbB).get(x + i, y + j);
						}
					}
					output.getBand(nbB).set(x, y, (sum / (size * size)));
				}
			}
		}
	}

	public static void color2Gray(Planar<GrayU8> input, Planar<GrayU8> output) {
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int r = input.getBand(0).get(x, y);
				int g = input.getBand(1).get(x, y);
				int b = input.getBand(2).get(x, y);
				int gray = (int) (0.3 * r + 0.59 * g + 0.11 * b);

				for (int nbB = 0; nbB < input.getNumBands(); nbB++) {
					output.getBand(0).set(x, y, gray);
					output.getBand(1).set(x, y, gray);
					output.getBand(2).set(x, y, gray);
				}
			}
		}
	}

	public static void hue(Planar<GrayU8> input, Planar<GrayU8> output, float hue) {
		Planar<GrayF32> rgb = new Planar<>(GrayF32.class, input.width, input.height, 3);
		float hueLevel = (float) Math.toRadians(hue);
		float tolerance = 0.01f;
		if (Math.abs(hueLevel - 2 * Math.PI) < tolerance) {
			hueLevel = 0;
		}

		for (int i = 0; i < input.getNumBands(); i++) {
			ConvertImage.convert(input.getBand(i), rgb.getBand(i));
		}

		Planar<GrayF32> hsv = rgb.createSameShape();
		ColorHsv.rgbToHsv(rgb, hsv);

		for (int y = 0; y < hsv.height; ++y) {
			for (int x = 0; x < hsv.width; ++x) {
				hsv.getBand(0).set(x, y, hueLevel);
			}
		}

		ColorHsv.hsvToRgb(hsv, rgb);

		for (int i = 0; i < rgb.getNumBands(); i++) {
			ConvertImage.convert(rgb.getBand(i), output.getBand(i));
		}
	}

	public static void main(String[] args) {

		// load image
		if (args.length < 2) {
			System.out.println("missing input or output image filename");
			System.exit(-1);
		}
		final String inputPath = args[0];
		BufferedImage image = UtilImageIO.loadImage(inputPath);
		if (image == null) {
			System.err.println("Cannot read input file '" + inputPath);
			System.exit(-1);
		}
		Planar<GrayU8> input = ConvertBufferedImage.convertFromPlanar(image, null, true, GrayU8.class);

		Planar<GrayU8> output = input.createSameShape();

		// processing

		// brightness(input, output, -50);
		// meanFilter(input, output, 11);
		// color2Gray(input, output);
		hue(input, output, 270);

		// save output image
		final String outputPath = args[1];
		UtilImageIO.saveImage(output, outputPath);
		System.out.println("Image saved in: " + outputPath);
	}

}