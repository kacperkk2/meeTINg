import controller.ExampleController;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Main {

    public static void main(String[] args) {
        AnnotationConfigApplicationContext context =
                new AnnotationConfigApplicationContext(AppConfig.class);

        ExampleController controller = (ExampleController) context.getBean("exampleController");

        controller.asdasd();

        context.close();

    }
}
