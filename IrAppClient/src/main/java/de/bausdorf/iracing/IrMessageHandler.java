package de.bausdorf.iracing;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

import javax.annotation.PostConstruct;
import javax.websocket.DeploymentException;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component
public class IrMessageHandler {
	private final Logger log = LoggerFactory.getLogger(this.getClass());

	@Value("${websocket.address}")
	private String wsAddress;
	
	private IrAppsClientEndpoint wsEndpoint;
	
	@PostConstruct
    public void initWsClient() {
        try {
            // open websocket
        	wsEndpoint = new IrAppsClientEndpoint(new URI(wsAddress));

            // add listener
        	wsEndpoint.addMessageHandler(new IrAppsClientEndpoint.MessageHandler() {
                public void handleMessage(String message) {
                    System.out.println(message);
                }
            });

            // send message to websocket
        	wsEndpoint.sendMessage("{'fps':'1','readIbt':'false', 'requestParameters':'__all_telemetry__'}");

            // wait 5 seconds for messages from websocket
            
            Thread.sleep(5000);

        } catch (InterruptedException ex) {
           log.error("InterruptedException exception: " + ex.getMessage());
        } catch (URISyntaxException ex) {
        	log.error("URISyntaxException exception: " + ex.getMessage());
        } catch (DeploymentException e) {
        	log.error(e.getMessage(), e);
		} catch (IOException e) {
        	log.error(e.getMessage(), e);
		}
    }
}
