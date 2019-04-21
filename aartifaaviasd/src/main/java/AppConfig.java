import controller.ExampleController;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import service.ExampleService;

@Configuration
public class AppConfig {

    @Bean
    public ExampleController exampleController() {
        return new ExampleController();
    }

    @Bean
    public ExampleService exampleService() {
        return new ExampleService();
    }
}
