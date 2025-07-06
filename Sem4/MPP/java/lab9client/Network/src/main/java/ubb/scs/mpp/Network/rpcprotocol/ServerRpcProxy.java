//package ubb.scs.mpp.Network.rpcprotocol;
//
//import com.google.gson.Gson;
//import ubb.scs.mpp.Network.dto.AngajatDTO;
//import ubb.scs.mpp.Network.dto.DTOUtils;
//import ubb.scs.mpp.Network.dto.SpetacolDTO;
//import ubb.scs.mpp.Service.IAppService;
//import ubb.scs.mpp.Service.ServiceException;
//import ubb.scs.mpp.Service.observer.Observer;
//import ubb.scs.mpp.model.Angajat;
//import ubb.scs.mpp.model.Bilet;
//import ubb.scs.mpp.model.Spectacol;
//
//import java.io.*;
//import java.net.Socket;
//import java.util.Arrays;
//import java.util.Date;
//import java.util.List;
//import java.util.concurrent.BlockingQueue;
//import java.util.concurrent.LinkedBlockingQueue;
//
//public class ServerRpcProxy implements IAppService {
//    private String host;
//    private int port;
//
//    private Observer client;
//    private BufferedReader input;
//    private PrintWriter output;
//    private Socket connection;
//    private BlockingQueue<Response> qresponses;
//    private volatile boolean finished;
//    private Gson gson;
//
//    public ServerRpcProxy(String host, int port) {
//        this.host = host;
//        this.port = port;
//        qresponses = new LinkedBlockingQueue<>();
//        gson = new Gson();
//    }
//
//    private void closeConnection() {
//        finished = true;
//        try {
//            input.close();
//            output.close();
//            connection.close();
//            client = null;
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//
//    private void sendRequest(Request request) throws ServiceException {
//        try {
//            String jsonRequest = gson.toJson(request);
//            output.println(jsonRequest);
//            output.flush();
//            System.out.println("Sent request: " + jsonRequest);
//        } catch (Exception e) {
//            throw new ServiceException("Error sending request " + e.getMessage());
//        }
//    }
//
//    private Response readResponse() {
//        try {
//           // String jsonResponse = qresponses.take();
//            System.out.println("Received response JSON: " + jsonResponse);
//            return gson.fromJson(jsonResponse, Response.class);
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
//        return null;
//    }
//
//    private void initializeConnection() {
//        try {
//            System.out.println("Initializing connection to " + host + ":" + port);
//            connection = new Socket(host, port);
//            input = new BufferedReader(new InputStreamReader(connection.getInputStream()));
//            output = new PrintWriter(new OutputStreamWriter(connection.getOutputStream()));
//            finished = false;
//            startReader();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//
//    private void startReader() {
//        Thread tw = new Thread(new ReaderThread());
//        tw.start();
//    }
//
//    private void handleUpdate(Response response) {
//        if (response.type() == ResponseType.ADDBILET) {
//            SpetacolDTO spectacolDTO = gson.fromJson(gson.toJson(response.data()), SpetacolDTO.class);
//            Spectacol spectacol = DTOUtils.fromSpetacolDTO(spectacolDTO);
//            System.out.println("Handle update: Updated spectacol " + spectacol);
//            try {
//                client.updatedSpectacol(spectacol);
//            } catch (Exception e) {
//                e.printStackTrace();
//            }
//        }
//    }
//
//    private boolean isUpdate(Response response) {
//        return response.type() == ResponseType.ADDBILET;
//    }
//
//    @Override
//    public Angajat login(Angajat ang, Observer observer) throws ServiceException {
//        initializeConnection();
//        AngajatDTO udto = DTOUtils.getAngajatDTO(ang);
//        Request req = new Request.Builder().type(RequestType.LOGIN).data(udto).build();
//        sendRequest(req);
//        Response response = readResponse();
//        if (response.type() != ResponseType.ERROR) {
//            this.client = observer;
//            AngajatDTO repsAng = gson.fromJson(gson.toJson(response.data()), AngajatDTO.class);
//            return DTOUtils.fromAngajatDTO(repsAng);
//        } else {
//            String err = response.data().toString();
//            closeConnection();
//            throw new ServiceException(err);
//        }
//    }
//
//    @Override
//    public Iterable<Spectacol> allSpectacol() throws ServiceException {
//        Request request = new Request.Builder().type(RequestType.GETSPECTACOLE).build();
//        sendRequest(request);
//        Response response = readResponse();
//        if (response.type() == ResponseType.OK) {
//            SpetacolDTO[] spectacole = gson.fromJson(gson.toJson(response.data()), SpetacolDTO[].class);
//            return () -> Arrays.stream(DTOUtils.fromSpetacolDTOs(List.of(spectacole))).iterator();
//        } else if (response.type() == ResponseType.ERROR) {
//            throw new ServiceException(response.data().toString());
//        }
//        return null;
//    }
//
//    @Override
//    public Iterable<Spectacol> getFilteredSpectacol(Date day) throws ServiceException {
//        Request request = new Request.Builder().type(RequestType.GETFSPECTACOLE).data(day).build();
//        sendRequest(request);
//        Response response = readResponse();
//        if (response.type() == ResponseType.OK) {
//            SpetacolDTO[] spectacole = gson.fromJson(gson.toJson(response.data()), SpetacolDTO[].class);
//            return () -> Arrays.stream(DTOUtils.fromSpetacolDTOs(List.of(spectacole))).iterator();
//        } else if (response.type() == ResponseType.ERROR) {
//            throw new ServiceException(response.data().toString());
//        }
//        return null;
//    }
//
//    @Override
//    public void addBilet(String buyer, Spectacol spec, int seats) throws ServiceException {
//        Bilet bilet = new Bilet(buyer, seats, spec);
//        Request request = new Request.Builder().type(RequestType.ADDBILET).data(bilet).build();
//        sendRequest(request);
//        Response response = readResponse();
//        if (response.type() == ResponseType.ERROR) {
//            throw new ServiceException(response.data().toString());
//        }
//    }
//
//    @Override
//    public void logout(Angajat angajat) throws ServiceException {
//        AngajatDTO udto = DTOUtils.getAngajatDTO(angajat);
//        Request req = new Request.Builder().type(RequestType.LOGOUT).data(udto).build();
//        sendRequest(req);
//        Response response = readResponse();
//        closeConnection();
//        if (response.type() == ResponseType.ERROR) {
//            throw new ServiceException(response.data().toString());
//        }
//    }
//
//    private class ReaderThread implements Runnable {
//        public void run() {
//            while (!finished) {
//                try {
//                    String jsonResponse = input.readLine();
//                    if (jsonResponse != null) {
//                        System.out.println("Received from server: " + jsonResponse);
//                        Response response = gson.fromJson(jsonResponse, Response.class);
//                        if (isUpdate(response)) {
//                            handleUpdate(response);
//                        } else {
//                            qresponses.put(jsonResponse);
//                        }
//                    }
//                } catch (IOException | InterruptedException e) {
//                    System.out.println("Reading error " + e);
//                }
//            }
//        }
//    }
//}
