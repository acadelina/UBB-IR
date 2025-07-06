package ubb.scs.mpp.Repository;

import org.hibernate.Session;
import ubb.scs.mpp.model.Bilet;
import ubb.scs.mpp.model.Spectacol;

import java.util.Objects;
import java.util.concurrent.atomic.AtomicReference;

public class BiletHibernateRepo implements BiletRepository {
    @Override
    public Iterable<Bilet> findBiletBySpectacol(Spectacol spectacol) throws RepoException {
        try(Session session=HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Bilet bilet where bilet.spectacol=?1",Bilet.class).setParameter(1,spectacol).getResultList();
        }
    }

    @Override
    public Bilet findOne(Long aLong) throws RepoException {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createSelectionQuery("from Bilet where id=:idM ", Bilet.class)
                    .setParameter("idM", aLong)
                    .getSingleResultOrNull();
        }
    }

    @Override
    public Iterable<Bilet> findAll() throws RepoException {
        try( Session session=HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("from Bilet ", Bilet.class).getResultList();
        }
    }

    @Override
    public Bilet save(Bilet entity) throws RepoException {
        HibernateUtils.getSessionFactory().inTransaction(session -> session.persist(entity));
        return entity;
    }

    @Override
    public Bilet delete(Long aLong) throws RepoException {
        AtomicReference<Bilet> bilet= new AtomicReference<>();
        HibernateUtils.getSessionFactory().inTransaction(session -> {
            bilet.set(session.createQuery("from Bilet where id=?1", Bilet.class).
                    setParameter(1, aLong).uniqueResult());
            System.out.println("In delete am gasit mesajul "+bilet);
            if (bilet.get() !=null) {
                session.remove(bilet);
                session.flush();
            }
        });
        return bilet.get();
    }

    @Override
    public Bilet update(Bilet entity) throws RepoException {
        HibernateUtils.getSessionFactory().inTransaction(session -> {
            if (!Objects.isNull(session.find(Bilet.class, entity.getId()))) {
                System.out.println("In update, am gasit biletul cu id-ul "+entity.getId());
                session.merge(entity);
                session.flush();
            }
        });
        return entity;
    }
}
