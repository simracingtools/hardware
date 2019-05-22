package de.bausdorf.iracing;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;

@SpringBootApplication
public class IrAppClientApplication {

    private static ApplicationContext applicationContext;

    @Autowired
    IrMessageHandler wsClient;
    
    public static void main(String[] args) {
        applicationContext = SpringApplication.run(IrAppClientApplication.class, args);
    }

}
