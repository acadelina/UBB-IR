package ubb.scs.mpp.Repository;


import ubb.scs.mpp.model.Bilet;
import ubb.scs.mpp.model.Spectacol;

public interface BiletRepository extends Repository <Long, Bilet> {
    Iterable<Bilet> findBiletBySpectacol(Spectacol spectacol) throws RepoException;
}
