package pdl.backend;

import java.io.IOException;
import java.util.List;
import java.util.Optional;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.ObjectNode;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
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

  public ImageController(ImageDao imageDao) {
    this.imageDao = imageDao;
  }

  @RequestMapping(value = "/images/{id}", method = RequestMethod.GET, produces = MediaType.IMAGE_JPEG_VALUE)
  public ResponseEntity<?> getImage(@PathVariable("id") long id) 
  {
    Optional<Image> img = imageDao.retrieve(id);
    if(img.isPresent()) {
      return ResponseEntity.ok()
        .contentType(MediaType.IMAGE_JPEG)
        .body(img.get().getData());
    }
    return new ResponseEntity<>("Image id="+id+" not found.", HttpStatus.NOT_FOUND);
  }

  @RequestMapping(value = "/images/{id}", method = RequestMethod.DELETE)
  public ResponseEntity<?> deleteImage(@PathVariable("id") long id) {
    Optional<Image> img = imageDao.retrieve(id);
    if(img.isPresent()){
      imageDao.delete(img.get());
      return new ResponseEntity<>("Image id="+id+" deleted.", HttpStatus.OK);
    }
    return new ResponseEntity<>("Image id="+id+" not found.", HttpStatus.NOT_FOUND);
  }

  @RequestMapping(value = "/images", method = RequestMethod.POST)
  public ResponseEntity<?> addImage(@RequestParam("file") MultipartFile file, RedirectAttributes redirectAttributes) {
    String type = file.getContentType();
    if(!(type.equals(MediaType.IMAGE_JPEG_VALUE) || type.equals(MediaType.IMAGE_PNG_VALUE)))
      return new ResponseEntity<>("Only JPEG file format supported", HttpStatus.UNSUPPORTED_MEDIA_TYPE);
    try {
      BufferedImage imgIO = ImageIO.read(file.getInputStream());
      int width = imgIO.getWidth();
      int height = imgIO.getHeight();
      String size = width+"x"+height;
      Image img = new Image(file.getOriginalFilename(),file.getBytes(),type,size.toString());
      imageDao.create(img);
      return new ResponseEntity<>("Image uploaded", HttpStatus.OK);
    }
    catch (final IOException e) {
      return new ResponseEntity<>("Failure to read file", HttpStatus.NO_CONTENT);
    }
  }

  @RequestMapping(value = "/images", method = RequestMethod.GET, produces = "application/json; charset=UTF-8")
  @ResponseBody
  public ArrayNode getImageList() {
    ArrayNode nodes = mapper.createArrayNode();
    List<Image> images = imageDao.retrieveAll();
    for(Image image: images){
      ObjectNode node = nodes.addObject();
      node.put("id", image.getId());
      node.put("name", image.getName());
      node.put("type", image.getType());
      node.put("size", image.getSize());
    }
    return nodes;
  }

}
