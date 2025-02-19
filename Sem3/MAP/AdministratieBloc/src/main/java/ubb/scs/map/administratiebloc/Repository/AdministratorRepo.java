package ubb.scs.map.administratiebloc.Repository;

import ubb.scs.map.administratiebloc.Domain.*;

import java.sql.*;
import java.util.ArrayList;
import java.util.Optional;

public class AdministratorRepo extends AbstractBDRepo<Long, Administrator> {
    PersoanaRepo persoanaRepo;
    BlocRepo blocRepo;
    public AdministratorRepo(String url, String username, String password,BlocRepo blocRepo,PersoanaRepo persoanaRepo) {
        super(url, username, password);
        this.persoanaRepo = persoanaRepo;
        this.blocRepo = blocRepo;
    }
    private ArrayList<Bloc> getBlocuri(Long idAdmin)
    {
        ArrayList<Bloc> blocs = new ArrayList<>();
        try(Connection connection = DriverManager.getConnection(url,username,password);
            PreparedStatement preparedStatement = connection.prepareStatement("select * from blocuri where administrator = ?");
        ){
            preparedStatement.setInt(1, Math.toIntExact(idAdmin));
            ResultSet resultSet=preparedStatement.executeQuery();
            while(resultSet.next())
            {

                Long id = resultSet.getLong("id");
                Long idAdresa= resultSet.getLong("adresa");
                Integer etaje= resultSet.getInt("etaje");

                ArrayList<Apartament> apartamente=blocRepo.apartamente(id);
                Bloc bloc=new Bloc(idAdresa,etaje,idAdmin,apartamente);

                bloc.setId(id);
                blocs.add(bloc);
            }
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return blocs;
    }

    @Override
    protected Administrator extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        Long idapartament = resultSet.getLong("apartament");
        Optional<Persoana> persoana=persoanaRepo.findOne(id);
        Persoana persoanaAux=persoana.isPresent()?persoana.get():null;

        Administrator admin=new Administrator(persoanaAux.getNume(),persoanaAux.getPrenume(),persoanaAux.getDataNasterii(),idapartament,getBlocuri(id));
        admin.setId(id);
        return admin;
    }

    @Override
    protected String getTableName() {
        return "administratori";
    }
}
