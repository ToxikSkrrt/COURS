package pdl.backend;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;

import javax.imageio.ImageIO;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.stereotype.Repository;

@Repository
public class ImageDao implements Dao<Image>, InitializingBean {
  @Autowired
  ImageRepository gallery;

  private final Map<Long, Image> images = new HashMap<>();

  public final Map<Long, Image> getMapImages(){
    return this.images;
  }

  public ImageDao() {
    File tmpdir = new File("").getAbsoluteFile();
    File dir = new File(tmpdir.getParent() + "/images");
    File filesList[] = dir.listFiles();

    for (File file : filesList) {
      String fileName = file.getName();

      Optional<String> test = Optional.ofNullable(fileName).filter(f -> f.contains("."))
          .map(f -> f.substring(fileName.lastIndexOf(".") + 1));

      if (!test.equals(Optional.ofNullable("png")) && !test.equals(Optional.ofNullable("jpg")))
        continue;

      try {
        BufferedImage imgtemp = ImageIO.read(file);
        byte[] fileContent = Files.readAllBytes(file.toPath());
        Image img = new Image(fileName, fileContent,
            test.equals(Optional.ofNullable("png")) ? MediaType.IMAGE_PNG : MediaType.IMAGE_JPEG,
            imgtemp.getWidth() + "*" + imgtemp.getHeight());
        images.put(img.getId(), img);
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
  }

  @Override
  public void afterPropertiesSet() throws Exception {
    for (Image img:images.values()){
      gallery.add(img);
    }
  }

  @Override
  public Optional<Image> retrieve(final long id) {
    return Optional.ofNullable(images.get(id));
  }

  @Override
  public List<Image> retrieveAll() {
    return new ArrayList<Image>(images.values());
  }

  @Override
  public void create(final Image img) {
    gallery.add(img);
    images.put(img.getId(), img);

    File tmpdir = new File("").getAbsoluteFile();
    File dir = new File(tmpdir.getParent() + "/images");

    File file = new File(dir, img.getName());
    try {
      file.createNewFile();
    } catch (IOException e) {
      e.printStackTrace();
    }
    try {
      FileOutputStream fos = new FileOutputStream(file);
      fos.write(img.getData());
      fos.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  @Override
  public void update(final Image img, final String[] params) {
    img.setName(Objects.requireNonNull(params[0], "Name cannot be null"));

    images.put(img.getId(), img);
  }

  @Override
  public void delete(final Image img) {
    gallery.delete(img.getId());
    images.remove(img.getId());

    File tmpdir = new File("").getAbsoluteFile();
    File file = new File(tmpdir.getParent() + "/images/" + img.getName());

    file.delete();
  }
}