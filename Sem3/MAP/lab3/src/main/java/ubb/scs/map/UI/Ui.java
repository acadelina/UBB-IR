package ubb.scs.map.UI;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Tuple;
import ubb.scs.map.domain.validators.EntityValidator;
import ubb.scs.map.domain.validators.ValidationException;
import ubb.scs.map.service.ServiceException;
import ubb.scs.map.service.ServiceFriendship;
import ubb.scs.map.service.ServiceUser;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Ui {
    private ServiceUser servUser;
    private ServiceFriendship servFriendship;
    private BufferedReader br=new BufferedReader(new InputStreamReader(System.in));

    public Ui(ServiceUser servUser, ServiceFriendship servFriendship) {
        this.servUser = servUser;
        this.servFriendship = servFriendship;
    }
    private void printMeniu()
    {
        System.out.println("Meniu:");
        System.out.println("1. Add user");
        System.out.println("2. Remove user");
        System.out.println("3. Add friendship");
        System.out.println("4. Remove friendship");
        System.out.println("5. Communities number");
        System.out.println("6. Social community");
        System.out.println("7. Exit");
    }

    private void callAddUser()  {
        try {
            String firstName, lastName, id;
            System.out.println("First Name: ");
            firstName = br.readLine();
            System.out.println("Last Name: ");
            lastName = br.readLine();
            System.out.println("Id: ");
            id = br.readLine();
            if(id!=null && id!="" && !id.isEmpty())
            {
                servUser.addUser(firstName, lastName, Long.parseLong(id));
                System.out.println("User added");
            }
            else {
                System.out.println("Invalid ID");
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        catch (ValidationException e)
        {
            System.out.println(e.getMessage());
        }


    }

    private void callRemoveUser() {
        try {
            String id;
            System.out.println("Id: ");
            id = br.readLine();
            if(id!=null&& !id.isEmpty()) {
                servFriendship.deleteAllFriendships(Long.parseLong(id));
                servUser.removeUser(Long.parseLong(id));
                System.out.println("User deleted succesfully");
            }
            else {
                System.out.println("Invalid ID");
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        } catch (ServiceException e) {
            System.out.println(e.getMessage());
        }

    }

    private void callAddFriendship() {
        try {
            String id1, id2;
            System.out.println("First user: ");
            id1 = br.readLine();
            System.out.println("Second user: ");
            id2 = br.readLine();
            if(id1!=null && id2!=null && !id1.isEmpty() && !id2.isEmpty()) {
                servFriendship.addFriendship(Long.parseLong(id1), Long.parseLong(id2));
                System.out.println("Friendship added");
            }
            else{
                System.out.println("Invalid ID");
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        catch (ServiceException e)
        {
            System.out.println(e.getMessage());
        }
    }

    private void callRemoveFriendship() {
        try {
            String id1, id2;
            System.out.println("First user: ");
            id1 = br.readLine();
            System.out.println("Second user: ");
            id2 = br.readLine();
            if(id1!=null && id2!=null && !id1.isEmpty() && !id2.isEmpty()) {
                servFriendship.removeFriendship(new Tuple(Long.parseLong(id1), Long.parseLong(id2)));
                System.out.println("Friendship removed succesfully");
            }
            else
            {
                System.out.println("Invalid ID");
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        catch (ServiceException e)
        {
            System.out.println(e.getMessage());
        }
    }

    private void callCommunitiesNumber()
    {
        System.out.println("Number of communities: "+servFriendship.communitiesNumber());
    }

    private void callSocialComunity()
    {
        System.out.println("Social comunity: "+servFriendship.socialCommunity());
    }

    public void run()
    {
        while(true) {
            printMeniu();
            System.out.println("Command: ");
            String command;
            try {
                command = br.readLine();
            } catch (IOException e) {
                System.out.println("Comanda invalida!");
                continue;
            }
            if (command.equals("1")) {
                callAddUser();

            }
            else if (command.equals("2")) {
                callRemoveUser();

            }
            else if (command.equals("3")) {
                callAddFriendship();

            }
            else if (command.equals("4")) {
                callRemoveFriendship();

            }
            else if(command.equals("5")) {
                callCommunitiesNumber();

            }
            else if(command.equals("6")) {
                callSocialComunity();

            }
            else if (command.equals("7")) {
                break;
            }
            else {
                System.out.println("Command invalida!");
            }
        }
    }
}
