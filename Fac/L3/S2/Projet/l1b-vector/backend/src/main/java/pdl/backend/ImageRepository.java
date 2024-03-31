package pdl.backend;
import java.io.IOException;
// import java.util.Arrays;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

@Repository
public class ImageRepository implements InitializingBean {
    @Autowired
    private JdbcTemplate jdbcTemplate;

    private final String SQl_DROP_TABLE = "DROP TABLE IF EXISTS images";
    private final String SQL_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS images (id bigserial PRIMARY KEY, name VARCHAR(255), histohs vector(144), historgb vector(1000))";
    private final String SQL_ADD_IMAGE = "INSERT INTO images (id, name, histohs, historgb) VALUES (?, ?, ?, ?)"; // +id +name +histHS +histoRGB
    private final String SQL_DELETE_IMAGE = "DELETE FROM images WHERE id = ?"; // +id
    private final String SQL_GET_HISTO_HS = "SELECT histohs FROM images WHERE id = ?"; // +id
    private final String SQL_GET_HISTO_RGB = "SELECT historgb FROM images WHERE id = ?"; // +id
    private final String SQL_GET_SIMILAR = "SELECT id FROM images ORDER BY histohs <-> ? LIMIT ?"; // +id +histo +many
    // private final String SQL_GET_DISTANCE = "SELECT ? <-> ?"; // +histo1 +histo2

    @Override
    public void afterPropertiesSet() throws Exception {
        // Drop table
        jdbcTemplate.execute(SQl_DROP_TABLE);
        // Create table
        this.jdbcTemplate.execute(SQL_CREATE_TABLE);
    }

    public void add(Image img) {
        try {
            double[] histoHS = Histogram.coupledHueSat(img);
            double[] histoRGB = Histogram.coupledRGB(img);
            jdbcTemplate.update(SQL_ADD_IMAGE, img.getId(), img.getName(), histoHS, histoRGB);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void delete(long id) {
        jdbcTemplate.update(SQL_DELETE_IMAGE, id);
    }

    @SuppressWarnings("deprecation")
    private double[] getHistoHS(long id){
        return jdbcTemplate.queryForObject(SQL_GET_HISTO_HS, new Object[]{id}, (rs, rowNum) -> (double[]) rs.getArray("histohs").getArray());
    }
    
    @SuppressWarnings("deprecation")
    public double[] getHistoRGB(long id) {
        return jdbcTemplate.queryForObject(SQL_GET_HISTO_RGB, new Object[]{id}, (rs, rowNum) -> (double[]) rs.getArray("historgb").getArray());
    }

    @SuppressWarnings("deprecation")
    public long[] getSimilar(long id, String histo, int many){
        double[] targetHisto;
        if (histo.equals("HS")) targetHisto = getHistoHS(id);
        else targetHisto = getHistoRGB(id);
        return jdbcTemplate.queryForObject(SQL_GET_SIMILAR, new Object[]{targetHisto, many}, (rs, rowNum) -> (long[]) rs.getArray("id").getArray());
    }

    // @SuppressWarnings("deprecation")
    // public double getDistance(long id1, long id2, String histo){
    //     double[] histo1;
    //     double[] histo2;
    //     if (histo.equals("HS")){
    //         histo1 = getHistoHS(id1);
    //         histo2 = getHistoHS(id2);
    //     } else {
    //         histo1 = getHistoRGB(id1);
    //         histo2 = getHistoRGB(id2);
    //     }
    //     return jdbcTemplate.queryForObject(SQL_GET_DISTANCE, new Object[]{((Object) Arrays.stream(histo1)).mapToDouble(Double::doubleValue).toArray(), Arrays.stream(histo2).mapToDouble(Double::doubleValue).toArray()}, Double.class);
    // }

}
