package pdl.backend;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Optional;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

@Repository
public class ImageRepository implements InitializingBean {

  @Autowired
  private JdbcTemplate jdbcTemplate;

  @Override
  public void afterPropertiesSet() throws Exception {
    // Drop table
    jdbcTemplate.execute("DROP TABLE IF EXISTS images");

    // Create table
    this.jdbcTemplate.execute("CREATE TABLE IF NOT EXISTS images (id bigserial PRIMARY KEY, name varchar(255),type varchar(255), size varchar(255), data BYTEA)");

  }

  public int getNbImages() {
    return jdbcTemplate.queryForObject("SELECT COUNT(*) FROM images", Integer.class);
  }

  public Optional<String> getImageName(long id) {
    try {
      return Optional.of(jdbcTemplate.queryForObject("SELECT name FROM images WHERE id = ?", String.class, id));
    }
    catch (DataAccessException e){
      return Optional.empty();
    }
  }

  public Optional<String> getImageType(long id) {
    try {
      return Optional.of(jdbcTemplate.queryForObject("SELECT type FROM images WHERE id = ?", String.class, id));
    }
    catch (DataAccessException e){
      return Optional.empty();
    }
  }

  public Optional<String> getImageSize(long id) {
    try {
      return Optional.of(jdbcTemplate.queryForObject("SELECT size FROM images WHERE id = ?", String.class, id));
    }
    catch (DataAccessException e){
      return Optional.empty();
    }
  }

  public Optional<byte[]> getImageData(long id) {
    try {
      return Optional.of(jdbcTemplate.queryForObject("SELECT data FROM images WHERE id = ?", byte[].class, id));
    }
    catch (DataAccessException e){
      return Optional.empty();
    }
  }

  public Image map2Image(Map<String, Object> obj){
    return new Image(
      (long)obj.get("id"),
      (String)obj.get("name"),
      (byte[])obj.get("data"),
      (String)obj.get("type"),
      (String)obj.get("size"));
  }

  public Optional<Image> getImage(long id) {
    try {
      Map<String, Object> query = jdbcTemplate.queryForMap("SELECT id, name, type, size, data FROM images WHERE id = ?", id);
      return Optional.of(map2Image(query));
    }
    catch (DataAccessException e){
      return Optional.empty();
    }
  }

  public  List<Image> getAllImages() {
    List<Image> result = new ArrayList<Image>();
    try {
      List<Map<String, Object>> query = jdbcTemplate.queryForList("SELECT id, name, type, size, data FROM images");
      for (Map<String, Object> obj : query){
        result.add(map2Image(obj));
      }
    }
    catch (DataAccessException e){}
    return result;
  }

  public void insertImage(String name, byte[] data, String type, String size) {
    jdbcTemplate.update("INSERT INTO images (name, data, type, size) VALUES (?, ?, ?, ?)", name, data, type, size);
  }

  public void deleteImage(long id) {
    jdbcTemplate.update("DELETE FROM images WHERE id = ?", id);
  }

  public void updateImage(long id, String name, byte[] data, String type, long size) {
    jdbcTemplate.update("UPDATE images SET name = ?, data = ?, type = ?, size = ? WHERE id = ?", name, data, type, size, id);
  }
}
