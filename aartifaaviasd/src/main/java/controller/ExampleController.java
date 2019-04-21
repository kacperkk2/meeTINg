package controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import service.ExampleService;

@Controller
public class ExampleController {

    @Autowired
    private ExampleService exampleService;

    public void asdasd() {
        exampleService.shout();
    }


}
