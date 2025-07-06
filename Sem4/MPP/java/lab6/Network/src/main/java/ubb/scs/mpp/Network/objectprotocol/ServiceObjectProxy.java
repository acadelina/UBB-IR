package ubb.scs.mpp.Network.objectprotocol;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Network.dto.AngajatDTO;
import ubb.scs.mpp.Network.dto.DTOUtils;
import ubb.scs.mpp.Service.IAppService;
import ubb.scs.mpp.Service.ServiceException;
import ubb.scs.mpp.Service.observer.Observer;
import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.model.Spectacol;

import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Arrays;
import java.util.Date;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ServiceObjectProxy implements IAppService {
    private final String host;
    private final int port;
    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;
    private final BlockingQueue<Response> qresponses;
    private volatile boolean finished;
    private static Logger logger = LogManager.getLogger(ServiceObjectProxy.class);
    Observer observer;


    public ServiceObjectProxy(String host, int port) {
        this.host = host;
        this.port = port;
        qresponses = new LinkedBlockingQueue<>();
    }

    protected void initializeConnection()  {
        try {
            connection=new Socket(host,port);
            output=new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input=new ObjectInputStream(connection.getInputStream());
            finished=false;
            startReader();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    private void startReader(){
        var readerThread = new Thread(new ServiceObjectProxy.ReaderThread());
        readerThread.start();
    }



    private class ReaderThread implements Runnable{
        public void run() {
            while(!finished && !connection.isClosed()){
                try {
                    Object response=input.readObject();
                    logger.info("Response: "+response);
                    if (response instanceof UpdatedSpectacolResponse){
                        handleUpdate((UpdatedSpectacolResponse)response);
                    }
                    else{
                        try {
                            qresponses.put((Response)response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }catch (EOFException e) {
                    logger.info("Conexiunea s-a închis, thread-ul Reader se oprește.");
                    finished = true;

                } catch (IOException | ClassNotFoundException e) {
                    logger.error(e);
                }
            }
            logger.debug("Reader thread stopped");
        }
    }


    protected void sendRequest(Request request) throws SendRequestException {
        try {
            if (connection == null || connection.isClosed()) {
                throw new SendRequestException("Connection is closed");
            }
            output.writeObject(request);
            output.flush();
        } catch (IOException e) {
            throw new SendRequestException("Error sending object "+e);
        }
    }

    protected Response readResponse() throws ReciveResponseException {
        Response response=null;
        try{
            response=qresponses.take();
        } catch (InterruptedException e) {
            logger.error(e);
            throw new ReciveResponseException("Error receiving object ");
        }
        return response;
    }

    protected void testConnectionOpen() throws ServiceException {
        if(connection==null){
            throw new ServiceException("Connection is not open");
        }
    }

    public void closeConnection() {
        System.out.println("Closing conn");
        finished=true;

        try{
            Thread.sleep(1000);
        }catch (Exception e)
        {
            e.printStackTrace();
        }
        try {
            input.close();
            output.close();
            connection.close();
            connection=null;
            logger.info("Connection closed");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Angajat login(String username, String password,Observer observer) throws ServiceException {
        initializeConnection();
        sendRequest(new LoginAngajatRequest(username,password));
        var response=readResponse();
        Angajat angajat=null;
        if(response instanceof LoginAngajatResponse){
            this.observer=observer;
            angajat= DTOUtils.fromAngajatDTO(((LoginAngajatResponse)response).getAngajat());
        }
        else if(response instanceof ErrorResponse){
            closeConnection();
            throw new ServiceException(((ErrorResponse)response).getMessage());
        }
        else {
            logger.error("Something went wrong");
            closeConnection();
        }
        return angajat;

    }

    @Override
    public Iterable<Spectacol> allSpectacol() throws ServiceException {
        testConnectionOpen();
        sendRequest(new GetAllSpectacoleRequest());
        var response = readResponse();
        Iterable<Spectacol> spectacole=null;
        if(response instanceof GetAllSpectacoleResponse){
            spectacole = ()-> Arrays.stream(DTOUtils.fromSpetacolDTOs(((GetAllSpectacoleResponse)response)
                            .getSpetacole()))
                    .iterator();
        }
        else {
            throw new ServiceException("Expected Spectacole, received " + response.getClass().getName());
        }
        return spectacole;
    }

    @Override
    public Iterable<Spectacol> getFilteredSpectacol(Date day) throws ServiceException {
        testConnectionOpen();
        sendRequest(new FilteredSpectacoleRequest(day));
        var response = readResponse();
        Iterable<Spectacol> spectacole=null;
        if(response instanceof FilteredSpectacoleResponse){
            spectacole = ()->Arrays.stream(DTOUtils.fromSpetacolDTOs(((FilteredSpectacoleResponse)response)
                            .getSpetacole()))
                    .iterator();
        }
        else {
            throw new ServiceException("Expected Spectacole, received " + response.getClass().getName());
        }
        return spectacole;
    }

    @Override
    public void addBilet(String buyer, Spectacol spec, int seats) throws ServiceException {
        testConnectionOpen();
        sendRequest(new ReserveBiletRequest(DTOUtils.getSpetacolDTO(spec), buyer, seats));
        var response = readResponse();
        if(!(response instanceof ReserveBiletResponse)){
            throw new ServiceException("Expected ReserveBiletResponse, received:\n " + response);
        }
    }

    @Override
    public void logout(Angajat a) throws ServiceException {
        testConnectionOpen();
        AngajatDTO ad=DTOUtils.getAngajatDTO(a);
        sendRequest(new LogoutRequest(ad));
        Response response=readResponse();

        closeConnection();

        if(response instanceof ErrorResponse){
            ErrorResponse er=(ErrorResponse)response;
            throw new ReciveResponseException(er.getMessage());
        }

    }

    public void handleUpdate(UpdatedSpectacolResponse update)
    {
        if (update instanceof UpdatedSpectacolResponse){
            var spectacol = ( update).getSpetacol();
            System.out.println("Handle:Updated spectacol "+spectacol);
            try {
                observer.updatedSpectacol(DTOUtils.fromSpetacolDTO(spectacol));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
