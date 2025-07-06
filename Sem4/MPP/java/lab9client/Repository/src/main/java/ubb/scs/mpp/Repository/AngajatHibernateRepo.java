package ubb.scs.mpp.Repository;

import org.hibernate.Session;
import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.model.Bilet;

import java.sql.SQLException;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicReference;

public class AngajatHibernateRepo implements AngajatRepository{
    @Override
    public Angajat findByUsernamePassword(String username, String password) throws SQLException, RepoException {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createSelectionQuery("from Angajat angajat where angajat.username =?1 and angajat.password =?2", Angajat.class)
                    .setParameter(1, username).setParameter(2, password)
                    .getSingleResultOrNull();
        }
    }

    @Override
    public Angajat findOne(Long aLong) throws RepoException {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createSelectionQuery("from Angajat angajat where angajat.id =?1", Angajat.class)
                    .setParameter(1, aLong)
                    .getSingleResultOrNull();
        }
    }

    @Override
    public Iterable<Angajat> findAll() throws RepoException {
        try( Session session=HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Angajat ", Angajat.class).getResultList();
        }
    }

    @Override
    public Angajat save(Angajat entity) throws RepoException {
        HibernateUtils.getSessionFactory().inTransaction(session -> session.persist(entity));
        return entity;
    }

    @Override
    public Angajat delete(Long aLong) throws RepoException {
        AtomicReference<Angajat> angajat= new AtomicReference<>();
        HibernateUtils.getSessionFactory().inTransaction(session -> {
            angajat.set(session.createQuery("from Angajat where id=?1", Angajat.class).
                    setParameter(1, aLong).uniqueResult());
            System.out.println("In delete am gasit mesajul "+angajat);
            if (angajat.get() !=null) {
                session.remove(angajat);
                session.flush();
            }
        });
        return angajat.get();
    }

    @Override
    public Angajat update(Angajat entity) throws RepoException {
        HibernateUtils.getSessionFactory().inTransaction(session -> {
            if (!Objects.isNull(session.find(Angajat.class, entity.getId()))) {
                System.out.println("In update, am gasit angajatul cu id-ul "+entity.getId());
                session.merge(entity);
                session.flush();
            }
        });
        return entity;
    }
}
