package ubb.scs.mpp.Repository;

import org.hibernate.Session;
import ubb.scs.mpp.model.Spectacol;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicReference;

public class SpectacolHibernateRepo implements SpectacolRepository {
    @Override
    public Iterable<Spectacol> findOnDate(Date date, Date date1) throws RepoException {
        LocalDateTime startDateTime = date.toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime();
        LocalDateTime endDateTime = date1.toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime();

        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createSelectionQuery("from Spectacol where data between :d1 and :d2", Spectacol.class)
                    .setParameter("d1", startDateTime).setParameter("d2", endDateTime).getResultList();

        }
    }

    @Override
    public Spectacol findOne(Long aLong) throws RepoException {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createSelectionQuery("from Spectacol where id=:idM ", Spectacol.class)
                    .setParameter("idM", aLong)
                    .getSingleResultOrNull();
        }
    }

    @Override
    public Iterable<Spectacol> findAll() throws RepoException {
        try( Session session=HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Spectacol ", Spectacol.class).getResultList();
        }
    }

    @Override
    public Spectacol save(Spectacol entity) throws RepoException {
        HibernateUtils.getSessionFactory().inTransaction(session -> session.persist(entity));
        return entity;
    }

    @Override
    public Spectacol delete(Long aLong) throws RepoException {
        AtomicReference<Spectacol> spec = new AtomicReference<>();

        HibernateUtils.getSessionFactory().inTransaction(session -> {
            Spectacol found = session.createQuery("from Spectacol where id = :id", Spectacol.class)
                    .setParameter("id", aLong)
                    .uniqueResult();

            System.out.println("In delete am gasit mesajul: " + found);

            if (found != null) {
                session.remove(found);  // NU remove(spec)!
                spec.set(found);
            }
        });

        return spec.get();
    }

    @Override
    public Spectacol update(Spectacol entity) throws RepoException {
        HibernateUtils.getSessionFactory().inTransaction(session -> {
            if (!Objects.isNull(session.find(Spectacol.class, entity.getId()))) {
                System.out.println("In update, am gasit spectacolul cu id-ul "+entity.getId());
                session.merge(entity);
                session.flush();
            }
        });
        return entity;
    }
}
