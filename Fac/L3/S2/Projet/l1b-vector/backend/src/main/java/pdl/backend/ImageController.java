package pdl.backend;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.List;
import java.util.Optional;

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

  @SuppressWarnings("null")
  @RequestMapping(value = "/images/{id}", method = RequestMethod.GET, produces = MediaType.IMAGE_JPEG_VALUE)
  public ResponseEntity<?> getImage(@PathVariable("id") long id) {

    Optional<Image> image = imageDao.retrieve(id);

    if (image.isPresent()) {
      return ResponseEntity.ok().contentType(MediaType.IMAGE_JPEG).body(image.get().getData());
    }
    return new ResponseEntity<>("Image id=" + id + " not found.", HttpStatus.NOT_FOUND);
  }

  @RequestMapping(value = "/images/{id}", method = RequestMethod.DELETE)
  public ResponseEntity<?> deleteImage(@PathVariable("id") long id) {

    Optional<Image> image = imageDao.retrieve(id);

    if (image.isPresent()) {
      imageDao.delete(image.get());
      return new ResponseEntity<>("Image id=" + id + " deleted.", HttpStatus.OK);
    }
    return new ResponseEntity<>("Image id=" + id + " not found.", HttpStatus.NOT_FOUND);
  }

  @SuppressWarnings("null")
  @RequestMapping(value = "/images", method = RequestMethod.POST)
  public ResponseEntity<?> addImage(@RequestParam("file") MultipartFile file, RedirectAttributes redirectAttributes) {

    String contentType = file.getContentType();
    if (!(contentType.equals(MediaType.IMAGE_JPEG.toString()) || contentType.equals(MediaType.IMAGE_PNG.toString()))) {
      return new ResponseEntity<>("Only JPEG / PNG file format supported", HttpStatus.UNSUPPORTED_MEDIA_TYPE);
    }
    try {
      BufferedImage imgtemp = ImageIO.read(ImageIO.createImageInputStream(file.getInputStream()));
      imageDao.create(new Image(file.getOriginalFilename(), file.getBytes(),
          contentType.equals(MediaType.IMAGE_JPEG.toString()) ? MediaType.IMAGE_JPEG : MediaType.IMAGE_PNG,
          imgtemp.getWidth() + "*" + imgtemp.getHeight()));
    } catch (IOException e) {
      return new ResponseEntity<>("Failure to read file", HttpStatus.UNSUPPORTED_MEDIA_TYPE);
    }
    return new ResponseEntity<>("Image uploaded", HttpStatus.CREATED);
  }

  @RequestMapping(value = "/images", method = RequestMethod.GET, produces = "application/json")
  @ResponseBody
  public ArrayNode getImageList() {
    List<Image> images = imageDao.retrieveAll();
    ArrayNode nodes = mapper.createArrayNode();
    for (Image image : images) {
      ObjectNode objectNode = mapper.createObjectNode();
      objectNode.put("id", image.getId());
      objectNode.put("name", image.getName());
      objectNode.put("type", image.getType().toString());
      objectNode.put("size", image.getSize());
      nodes.add(objectNode);
    }
    return nodes;
  }

}
