# Importer images au lancement

`ImageDao.java`
```java
package pdl.backend;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;

import org.springframework.stereotype.Repository;

@Repository
public class ImageDao implements Dao<Image> {

  private final Map<Long, Image> images = new HashMap<>();

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
        byte[] fileContent = Files.readAllBytes(file.toPath());
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
    img.setName(Objects.requireNonNull(params[0], "Name cannot be null"));

    images.put(img.getId(), img);
  }

  @Override
  public void delete(final Image img) {
    images.remove(img.getId());
  }
}

```