package imageprocessing;

import boofcv.alg.filter.blur.BlurImageOps;
import boofcv.core.image.ConvertImage;
import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayS16;
import boofcv.struct.image.GrayU8;

public class Convolution {

  public static void meanFilter(GrayU8 input, GrayU8 output, int size) {
    for (int y = size / 2; y < input.height - (size / 2); ++y) {
      for (int x = size / 2; x < input.width - (size / 2); ++x) {
        int sum = 0;
        for (int j = -size / 2; j <= size / 2; j++) {
          for (int i = -size / 2; i <= size / 2; i++) {
            sum += input.get(x + i, y + j);
          }
        }
        output.set(x, y, (sum / (size * size)));
      }
    }
  }

  public static void convolution(GrayU8 input, GrayS16 output, int[][] kernel) {
    int n = (kernel.length - 1) / 2;
    for (int y = n; y < input.height - n; ++y) {
      for (int x = n; x < input.width - n; ++x) {
        int r = 0;
        for (int u = -n; u <= n; u++) {
          for (int v = -n; v <= n; v++) {
            r += input.get(x + u, y + v) * kernel[u + n][v + n];
          }
        }
        output.set(x, y, r);
      }
    }
  }

  public static void gradientImage(GrayU8 input, GrayU8 output, int[][] kernelX, int[][] kernelY) {
    GrayS16 outputX = new GrayS16(input.width, input.height);
    GrayS16 outputY = new GrayS16(input.width, input.height);

    convolution(input, outputX, kernelX);
    convolution(input, outputY, kernelY);

    for (int y = 0; y < input.height; ++y) {
      for (int x = 0; x < input.width; ++x) {
        int gx = outputX.get(x, y);
        int gy = outputY.get(x, y);
        int norme = (int) Math.sqrt(gx * gx + gy * gy);
        output.set(x, y, norme);
      }
    }
  }

  public static void gradientImageSobel(GrayU8 input, GrayU8 output) {
    int[][] kernelX = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
    int[][] kernelY = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };
    gradientImage(input, output, kernelX, kernelY);
  }

  public static void gradientImagePrewitt(GrayU8 input, GrayU8 output) {
    int[][] kernelX = { { -1, 0, 1 }, { -1, 0, 1 }, { -1, 0, 1 } };
    int[][] kernelY = { { -1, -1, -1 }, { 0, 0, 0 }, { 1, 1, 1 } };
    gradientImage(input, output, kernelX, kernelY);
  }

  public static void main(final String[] args) {
    // load image
    if (args.length < 2) {
      System.out.println("missing input or output image filename");
      System.exit(-1);
    }
    final String inputPath = args[0];
    GrayU8 input = UtilImageIO.loadImage(inputPath, GrayU8.class);
    GrayU8 output = input.createSameShape();

    // processing
    // meanFilter(input, output, 77);
    // gradientImageSobel(input, output);
    gradientImagePrewitt(input, output);

    // save output image
    final String outputPath = args[1];
    UtilImageIO.saveImage(output, outputPath);
    System.out.println("Image saved in: " + outputPath);
  }

}
