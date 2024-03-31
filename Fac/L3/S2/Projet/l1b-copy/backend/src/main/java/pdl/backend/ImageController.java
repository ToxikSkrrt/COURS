package pdl.backend;

// import java.io.ByteArrayInputStream;
// import java.io.File;
// import java.io.FileOutputStream;
import java.io.IOException;
// import java.io.InputStream;
import java.util.List;
// import java.util.Optional;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ArrayNode;
// import com.fasterxml.jackson.databind.node.ObjectNode;

import org.springframework.beans.factory.annotation.Autowired;
// import org.springframework.core.io.ClassPathResource;
// import org.springframework.core.io.InputStreamResource;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
// import org.springframework.util.StreamUtils;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

@RestController
public class ImageController {

  @Autowired
  private ObjectMapper mapper;

  private final ImageDao imageDao;

  @Autowired
  public ImageController(ImageDao imageDao) {
    this.imageDao = imageDao;
  }

  @SuppressWarnings("null")
  @RequestMapping(value = "/images/{id}", method = RequestMethod.GET, produces = MediaType.IMAGE_JPEG_VALUE)
  public ResponseEntity<?> getImage(@PathVariable("id") long id) {
    if (imageDao.retrieve(id).isPresent()){
      byte[] bytes = imageDao.retrieve(id).get().getData();
      return ResponseEntity.ok().contentType(MediaType.IMAGE_JPEG).body(bytes);
    } return new ResponseEntity<>(HttpStatus.NOT_FOUND);
  }

  @RequestMapping(value = "/images/{id}", method = RequestMethod.DELETE)
  public ResponseEntity<?> deleteImage(@PathVariable("id") long id) {
    var img = imageDao.retrieve(id);
    if (img.isPresent()){
      imageDao.delete(img.get());
      return new ResponseEntity<>(HttpStatus.OK);
    } return new ResponseEntity<>(HttpStatus.NOT_FOUND);
  }

  @SuppressWarnings("null")
  @RequestMapping(value = "/images", method = RequestMethod.POST)
  public ResponseEntity<?> addImage(@RequestParam("file") MultipartFile file,
      RedirectAttributes redirectAttributes) {
    if (!file.getContentType().equalsIgnoreCase("image/jpeg")) {
      return new ResponseEntity<>(HttpStatus.UNSUPPORTED_MEDIA_TYPE);
    }
    try {
      Image convimg = new Image(file.getOriginalFilename(), file.getBytes());
      imageDao.create(convimg);
      return new ResponseEntity<>(HttpStatus.OK);
    } catch (IOException e) {
      e.printStackTrace();
      return new ResponseEntity<>(HttpStatus.UNSUPPORTED_MEDIA_TYPE);
    }
  }

  @RequestMapping(value = "/images", method = RequestMethod.GET, produces = "application/json; charset=UTF-8")
  @ResponseBody
  public ArrayNode getImageList() {
    ArrayNode nodes = mapper.createArrayNode();
    List<Image> imgList = imageDao.retrieveAll();

    for (int i=0; i<imgList.size(); i++){
      nodes.addObject()
      .put("names", imgList.get(i).getName())
      .put("id", imgList.get(i).getId());
    }
    return nodes;
  }

}
