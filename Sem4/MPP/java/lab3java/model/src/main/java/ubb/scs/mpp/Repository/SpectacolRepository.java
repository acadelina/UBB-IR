package ubb.scs.mpp.Repository;

import ubb.scs.mpp.Domain.Spectacol;

import java.util.Date;

public interface SpectacolRepository extends Repository <Long, Spectacol> {
    Iterable<Spectacol> findOnDate(Date date,Date date1) throws RepoException;
}
