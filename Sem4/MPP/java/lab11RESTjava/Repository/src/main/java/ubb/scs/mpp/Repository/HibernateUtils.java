package ubb.scs.mpp.Repository;


import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import ubb.scs.mpp.model.Bilet;
import ubb.scs.mpp.model.Spectacol;

public class HibernateUtils {

    private static SessionFactory sessionFactory;

    public static SessionFactory getSessionFactory(){
        if ((sessionFactory==null)||(sessionFactory.isClosed()))
            sessionFactory=createNewSessionFactory();
        return sessionFactory;
    }

    private static  SessionFactory createNewSessionFactory(){
        sessionFactory = new Configuration()
                .addAnnotatedClass(Bilet.class)
                .addAnnotatedClass(Spectacol.class)
                .buildSessionFactory();
        return sessionFactory;
    }

    public static  void closeSessionFactory(){
        if (sessionFactory!=null)
            sessionFactory.close();
    }
}
