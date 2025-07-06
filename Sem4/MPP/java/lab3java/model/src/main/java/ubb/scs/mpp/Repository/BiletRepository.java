package ubb.scs.mpp.Repository;

import ubb.scs.mpp.Domain.Bilet;
import ubb.scs.mpp.Domain.Spectacol;

public interface BiletRepository extends Repository <Long, Bilet> {
    Iterable<Bilet> findBiletBySpectacol(Spectacol spectacol) throws RepoException;
}
