package ubb.scs.mpp.Network.objectprotocol;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Network.dto.DTOUtils;
import ubb.scs.mpp.Service.IAppService;
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
import java.util.stream.StreamSupport;

public class ClientObjectWorker implements Runnable, Observer {

    private static Logger logger = LogManager.getLogger(ClientObjectWorker.class);

    private final IAppService appService;
    private final Socket socket;
    private final ObjectInputStream input;
    private final ObjectOutputStream output;
    private volatile boolean connected;

    public ClientObjectWorker(final IAppService appService, final Socket socket) {
        this.appService = appService;
        this.socket = socket;

        ObjectInputStream in=null;
        ObjectOutputStream out=null;

        try{
            out=new ObjectOutputStream(socket.getOutputStream());
            out.flush();
            in=new ObjectInputStream(socket.getInputStream());
            connected=true;
        } catch (IOException e) {
            logger.error(e);
            logger.error(e.getStackTrace());
        }
        input=in;
        output=out;
    }

    @Override
    public void run() {
        while(connected){
            try {
                Object request=input.readObject();
                Response response=handleRequest((Request)request);
                if (response!=null){
                    sendResponse(response);
                }
            } catch (EOFException e) {
                logger.info("Client conection closed");

            }catch (Exception e) {
                logger.error(e);
            }
            try{
                Thread.sleep(1000);
            }
            catch (InterruptedException e) {
                logger.error(e);
            }}
            try {
                input.close();
                output.close();
                socket.close();
            } catch (IOException e) {
                logger.error("Error "+e);
            }



    }



    private Response handleRequest(Request request){

        Response response = null;
        if(request instanceof GetAllSpectacoleRequest){
            logger.debug("GetAllSpectacoleRequest");
            try {
                response = new GetAllSpectacoleResponse(StreamSupport
                        .stream(appService.allSpectacol().spliterator(), false)
                        .toArray(Spectacol[]::new));
            } catch (Exception e) {
                response = new ErrorResponse(e.getMessage());
            }
        }
        if(request instanceof FilteredSpectacoleRequest){
            logger.debug("FilteredSpectacoleRequest");
            try {
                var spectacole = appService.getFilteredSpectacol(((FilteredSpectacoleRequest) request).getDay());
                response = new FilteredSpectacoleResponse(StreamSupport
                        .stream(spectacole.spliterator(), false)
                        .toArray(Spectacol[]::new));
            } catch (Exception e) {
                System.out.println(e.getMessage());
                e.printStackTrace();
                response = new ErrorResponse(e.getMessage());
            }
        }
        else if(request instanceof LoginAngajatRequest){
            logger.debug("LoginAngajatRequest");
            try {
                var ang=new Angajat(((LoginAngajatRequest) request).getUsername(),((LoginAngajatRequest)request).getPassword(),"");
                var angajat = appService.login(ang,this);

                response = new LoginAngajatResponse(DTOUtils.getAngajatDTO(angajat));
            } catch (Exception e) {
                connected=false;
                response = new ErrorResponse(e.getMessage());
            }
        }
        if(request instanceof ReserveBiletRequest){
            logger.debug("ReserveBiletRequest");
            try{
                var spectacol =((ReserveBiletRequest) request).getSpetacol();
                var cumparator = ((ReserveBiletRequest) request).getBuyer();
                var seats = ((ReserveBiletRequest) request).getSeats();
                appService.addBilet(cumparator,DTOUtils.fromSpetacolDTO(spectacol), seats);
                response = new ReserveBiletResponse();
            } catch (ServiceException  e) {
                response = new ErrorResponse(e.getMessage());
            }
        }
        if(request instanceof LogoutRequest)
        {
            logger.debug("LogoutRequest");
            try{
                appService.logout(((LogoutRequest) request).getAngajat().toAngajat());
                response = new LogoutResponse();
            } catch (ServiceException e) {
                response = new ErrorResponse(e.getMessage());
            }
            connected=false;
        }
        if(request instanceof DeleteSpectacolRequest)
        {
            logger.debug("DeleteShow");
            try{
                appService.deleteSpectacol(((DeleteSpectacolRequest) request).getId());
                response=new DeleteSpectacolResponse();
            } catch (ServiceException e) {
                response=new ErrorResponse(e.getMessage());
            }
        }
        if(response==null)
            response = new ErrorResponse("No response");
        return response;
    }


    private void sendResponse(Response response) throws IOException {
        logger.debug("sendResponse");
        synchronized (output) {
            output.writeObject(response);
            output.flush();
        }
    }

    @Override
    public void updatedSpectacol(Spectacol s) {
        logger.debug("Updated spectacol ");
        var sDto = DTOUtils.getSpetacolDTO(s);
        try {
            sendResponse(new UpdatedSpectacolResponse(sDto));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
