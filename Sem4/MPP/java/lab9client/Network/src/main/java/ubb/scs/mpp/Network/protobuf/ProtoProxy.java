package ubb.scs.mpp.Network.protobuf;

import ubb.scs.mpp.Service.IAppService;
import ubb.scs.mpp.Service.ServiceException;
import ubb.scs.mpp.Service.observer.Observer;
import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.model.Bilet;
import ubb.scs.mpp.model.Spectacol;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Arrays;
import java.util.Date;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ProtoProxy implements IAppService {
    private String host;
    private int port;

    private Observer client;

    private InputStream input;
    private OutputStream output;
    private Socket connection;

    private BlockingQueue<BileteProtobufs.TicketResponse> qresponses;
    private volatile boolean finished;
    public ProtoProxy(String host, int port) {
        this.host = host;
        this.port = port;
        qresponses=new LinkedBlockingQueue<BileteProtobufs.TicketResponse>();
    }

    @Override
    public Angajat login(Angajat user,Observer client) throws ServiceException {
        try{
            initializeConnection();
            System.out.println("Login request ...");
            sendRequest(ProtoUtils.createLoginRequest(user));
            BileteProtobufs.TicketResponse response=readResponse();
            if (response.getType()==BileteProtobufs.TicketResponse.Type.Ok){
                this.client=client;
                return ProtoUtils.getUser(response);
            }
            if (response.getType()==BileteProtobufs.TicketResponse.Type.Error){
                String errorText=ProtoUtils.getError(response);
                closeConnection();
                throw new ServiceException(errorText);
            }
        }catch (Exception e){
            throw new ServiceException(e.getMessage());
        }

        return null;
    }

    @Override
    public void logout(Angajat user) throws ServiceException {
        try {
            sendRequest(ProtoUtils.createLogoutRequest(user));
            BileteProtobufs.TicketResponse response=readResponse();
            closeConnection();
            if (response.getType()==BileteProtobufs.TicketResponse.Type.Error){
                String errorText=ProtoUtils.getError(response);
                throw new Exception(errorText);
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

    }

    @Override
    public void deleteSpectacol(long id) throws ServiceException {

    }


    private void closeConnection() {
        finished=true;
        try {
            input.close();
            output.close();
            connection.close();
            client=null;
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private void sendRequest(BileteProtobufs.Request request)throws Exception{
        try {
            System.out.println("Sending request ..."+request);
            request.writeDelimitedTo(output);
            output.flush();
            System.out.println("Request sent.");
        } catch (IOException e) {
            throw new Exception("Error sending object "+e);
        }

    }

    private BileteProtobufs.TicketResponse readResponse() throws Exception{
        BileteProtobufs.TicketResponse response=null;
        try{
            response=qresponses.take();

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return response;
    }
    private void initializeConnection() throws Exception{
        try {
            connection=new Socket(host,port);
            output=connection.getOutputStream();
            input=connection.getInputStream();     //new ObjectInputStream(connection.getInputStream());
            finished=false;
            startReader();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private void startReader(){
        Thread tw=new Thread(new ReaderThread());
        tw.start();
    }


    private void handleUpdate(BileteProtobufs.TicketResponse updateResponse) {
        Spectacol spec = ProtoUtils.getSpectacol(updateResponse);
        try {
            client.updatedSpectacol(spec);
        } catch (Exception e) {
            e.printStackTrace();
        }

    }



    @Override
    public Iterable<Spectacol> allSpectacol() throws ServiceException {
        try{
            sendRequest(ProtoUtils.createGetShowsRequest());
            BileteProtobufs.TicketResponse response=readResponse();
            if (response.getType()==BileteProtobufs.TicketResponse.Type.ShowList){
                return Arrays.stream(ProtoUtils.getSpectacole(response)).toList();
            }
            if (response.getType()==BileteProtobufs.TicketResponse.Type.Error){
                String errorText=ProtoUtils.getError(response);
                throw new ServiceException(errorText);
            }
        }
        catch (Exception e){
            throw new ServiceException(e.getMessage());
        }
        return null;
    }

    @Override
    public Iterable<Spectacol> getFilteredSpectacol(Date day) throws ServiceException {
        try{
            sendRequest(ProtoUtils.createGetFShowsRequest(day));
            BileteProtobufs.TicketResponse response=readResponse();
            if (response.getType()==BileteProtobufs.TicketResponse.Type.ShowList){
                return Arrays.stream(ProtoUtils.getSpectacole(response)).toList();
            }
            if (response.getType()==BileteProtobufs.TicketResponse.Type.Error){
                String errorText=ProtoUtils.getError(response);
                throw new ServiceException(errorText);
            }
        }
        catch (Exception e){
            throw new ServiceException(e.getMessage());
        }
        return null;
    }

    @Override
    public void addBilet(String buyer, Spectacol spec, int seats) throws ServiceException {
        try{
            sendRequest(ProtoUtils.createAddBiletRequest(new Bilet(buyer,seats,spec)));
            BileteProtobufs.TicketResponse response=readResponse();

            if (response.getType()==BileteProtobufs.TicketResponse.Type.Error){
                String errorText=ProtoUtils.getError(response);
                throw new ServiceException(errorText);
            }
        }
        catch (Exception e){
            throw new ServiceException(e.getMessage());
        }
    }



    private class ReaderThread implements Runnable{
        public void run() {
            while(!finished){
                try {
                    BileteProtobufs.TicketResponse response=BileteProtobufs.TicketResponse.parseDelimitedFrom(input);
                    System.out.println("response received "+response);

                    if ((response.getType()== BileteProtobufs.TicketResponse.Type.NewTicket)){
                        handleUpdate(response);
                    }else{
                        try {
                            qresponses.put(response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException e) {
                    System.out.println("Reading error "+e);
                }
            }
        }
    }


}
