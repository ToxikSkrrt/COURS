package pdl.backend;

import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

import org.springframework.core.io.ClassPathResource;
import org.springframework.stereotype.Repository;

@Repository
public class ImageDao implements Dao<Image> {

  private final Map<Long, Image> images = new HashMap<>();

  public ImageDao() {
    for (int i = 0; i <= 8; i++) {
      String fileName = "f" + i + ".png";
      final ClassPathResource imgFile = new ClassPathResource(fileName);

      try {
        byte[] fileContent = Files.readAllBytes(imgFile.getFile().toPath());
        Image img = new Image(fileName, fileContent);
        images.put(img.getId(), img);
      } catch (IOException e) {
          e.printStackTrace();
      }
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
    images.put(img.getId(), img);
  }

  @Override
  public void update(final Image img, final String[] params) {
    // Not used
  }

  @Override
  public void delete(final Image img) {
    images.remove(img.getId());
  }
}
