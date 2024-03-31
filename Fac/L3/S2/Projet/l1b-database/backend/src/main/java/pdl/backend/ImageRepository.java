package pdl.backend;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
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
        this.jdbcTemplate.execute(
                "CREATE TABLE IF NOT EXISTS images (id serial PRIMARY KEY, histo2d vector(9000), histo3d vector(4096))");

    }

    public int getNbImages() {
        return (int) jdbcTemplate.queryForObject("SELECT COUNT(*) FROM images",
                Integer.class);
    }

    public String getImageName(long id) {
        return jdbcTemplate.queryForObject("SELECT name FROM images WHERE id = ?",
                String.class, id);
    }
}
