package pdl.backend;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Optional;

import org.springframework.core.io.ClassPathResource;
import org.springframework.stereotype.Repository;
import java.net.URLConnection;

import jakarta.annotation.PostConstruct;

import org.springframework.beans.factory.annotation.Autowired;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;

@Repository
public class ImageDao implements Dao<Image> {

  private final static String image_folder_name = "images/";

  @Autowired
  private ImageRepository imgRepo;

  @PostConstruct
  public void init(){
    LoadImageFolder();
  }

  public void LoadImageFolder(){
    final ClassPathResource folder = new ClassPathResource(image_folder_name);
    try {
      for (String file : folder.getFile().list()) {
        Optional<Image> img = LoadImage(image_folder_name+file);
        if(img.isPresent())
          create(img.get());
      }
    } catch (final IOException e) {
      System.err.println("Failed to load images");
    }
  }

  public static Optional<Image> LoadImage(final String path){
    final ClassPathResource file = new ClassPathResource(path);
    try {
      BufferedImage imgIO = ImageIO.read(file.getInputStream());
      String type = URLConnection.guessContentTypeFromName(file.getFilename());
      byte[] content = file.getContentAsByteArray();
      String size = imgIO.getWidth() + "x" + imgIO.getHeight();
      return Optional.of(new Image(file.getFilename(), content, type, size));
    }
    catch (final IOException e) {
      System.err.println("Failed to load image: "+path);
      return Optional.empty();
    }
  }

  @Override
  public Optional<Image> retrieve(final long id) {
    return imgRepo.getImage(id);
  }

  @Override
  public List<Image> retrieveAll() {
    return imgRepo.getAllImages();
  }

  @Override
  public void create(final Image img) {
    if(img!=null){
      imgRepo.insertImage(img.getName(),img.getData(),img.getType().toString(),img.getSize());
    }
  }

  @Override
  public void update(final Image img, final String[] params) {
    // this method is void cause not used, comment it generate a warning
  }

  @Override
  public void delete(final Image img) {
    if(img!=null){
      imgRepo.deleteImage(img.getId());
    }
  }

}
