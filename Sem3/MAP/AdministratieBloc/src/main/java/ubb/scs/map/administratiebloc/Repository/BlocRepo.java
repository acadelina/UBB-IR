package ubb.scs.map.administratiebloc.Repository;

import ubb.scs.map.administratiebloc.Domain.Apartament;
import ubb.scs.map.administratiebloc.Domain.Bloc;
import ubb.scs.map.administratiebloc.Domain.TipApartament;

import java.sql.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Optional;

public class BlocRepo extends AbstractBDRepo<Long,Bloc> {

    protected final String url;
    protected final String username;
    protected final String password;
    public BlocRepo(String url, String username, String password) {
        super(url, username, password);

        this.url = url;
        this.username = username;
        this.password = password;
    }

    protected ArrayList<Apartament> apartamente(Long idBloc)
    {
        ArrayList<Apartament> apartamente = new ArrayList<>();
        try(Connection connection = DriverManager.getConnection(url,username,password);
            PreparedStatement preparedStatement = connection.prepareStatement("select * from apartamente where idbloc = ?");
            ){
            preparedStatement.setInt(1, Math.toIntExact(idBloc));
            ResultSet resultSet=preparedStatement.executeQuery();
            while(resultSet.next())
            {

                Long id=resultSet.getLong("id");
                Long idbloc=resultSet.getLong("idbloc");
                Integer nrapartamnt=resultSet.getInt("nrapartament");
                Integer nrcamere=resultSet.getInt("nrcamere");
                String tip=resultSet.getString("tip");
                Integer suprafata=resultSet.getInt("suprafata");
                TipApartament tipApartament=TipApartament.valueOf(tip);

                Apartament apartament=new Apartament(idbloc,nrapartamnt,nrcamere,tipApartament,suprafata);

                apartament.setId(id);
                apartamente.add(apartament);
            }
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return apartamente;

    }

    @Override
    protected Bloc extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        Long idAdresa= resultSet.getLong("adresa");
        Integer etaje= resultSet.getInt("etaje");
        Long idAdmin= resultSet.getLong("administrator");
        ArrayList<Apartament> apartamente= apartamente(id);
        Bloc bloc=new Bloc(idAdresa,etaje,idAdmin,apartamente);
        return bloc;
    }



    @Override
    protected String getTableName() {
        return "bloc";
    }
}
