package pdl.backend;
import boofcv.alg.color.ColorHsv;
import boofcv.io.image.ConvertBufferedImage;
import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayF32;
import boofcv.struct.image.Planar;
import java.awt.image.BufferedImage;


public class Histogram {
	private static float[] hueSaturationHistogram(Planar<GrayF32> input) {
		int[][] histogram = new int[180][50];
		Planar<GrayF32> hsv = input.createSameShape();
		ColorHsv.rgbToHsv(input, hsv);

		for (int y = 0; y < hsv.height; ++y) {
			for (int x = 0; x < hsv.width; ++x) {
				int tint = (int)Math.toDegrees(hsv.getBand(0).get(x, y));
				tint /= 2;
				if (tint>179) tint = 1799;
				if (tint<0) tint = 0;
				int saturation = (int)(hsv.getBand(1).get(x,y)*100);
				saturation /= 2;
				if (saturation>49) saturation = 49;
				if (saturation<0) saturation = 0;
				histogram[tint][saturation]++;
			}
		}
		return flatten2DHistogram(histogram);
	}

	private static float[] rgbHistogram(Planar<GrayF32> input) {
		int[][][] histogram = new int[16][16][16];
		for (int y = 0; y < input.height; ++y) {
			for (int x = 0; x < input.width; ++x) {
				int red = (int)input.getBand(0).get(x,y);
				red /= 16;
                if (red>16) red = 16;
				if (red<0) red = 0;
                int green = (int)input.getBand(1).get(x, y);
				green /= 16;
                if (green>16) green = 16;
				if (green<0) green = 0;
                int blue = (int)input.getBand(2).get(x, y);
				blue /= 16;
                if (blue>16) blue = 16;
				if (blue<0) blue = 0;
				histogram[red][green][blue]++;
			}
		}
		return flatten3DHistogram(histogram);
	}

	public static float[] flatten2DHistogram(int[][] histogram) {
		float[] histo2d = new float[histogram.length * histogram[0].length];
		int count = 0;
		for (int i = 0; i < histogram.length; i++) {
			for (int j = 0; j < histogram[i].length; j++) {
				histo2d[count] = (float) histogram[i][j];
				count++;
			}
		}
		return histo2d;
	}

	public static float[] flatten3DHistogram(int[][][] histogram) {
		float[] histo3d = new float[histogram.length * histogram[0].length * histogram[0][0].length];
		int count = 0;
		for (int i = 0; i < histogram.length; i++) {
			for (int j = 0; j < histogram[i].length; j++) {
				for (int k = 0; k < histogram[i][j].length; k++) {
					histo3d[count] = (float) histogram[i][j][k];
					count++;
				}
			}
		}
		return histo3d;
	}

	public static void loadCreate (final String inputPath){
		BufferedImage input = UtilImageIO.loadImage(inputPath);
		if(input == null) {
			System.err.println("Cannot read input file '" + inputPath);
			System.exit(-1);
		}
		Planar<GrayF32> Img32 = ConvertBufferedImage.convertFromPlanar(input, null, true, GrayF32.class);
		float[] hs = hueSaturationHistogram(Img32);
		float[] rgb = rgbHistogram(Img32);
		// Appeler méthode Add depuis ImageRepository (pour ajouter histo 2D et 3D à
		// Database)

	}
}
