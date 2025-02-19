package ubb.scs.map.anar.Domain;


public class Entity<ID>  {

    private ID id;
    private Long serialVersionUID;

    public Long getSerialVersionUID() {
        return serialVersionUID;
    }

    public void setSerialVersionUID(Long serialVersionUID) {
        this.serialVersionUID = serialVersionUID;
    }

    public ID getId() {
        return id;
    }
    public void setId(ID id) {
        this.id =  id;
    }
}