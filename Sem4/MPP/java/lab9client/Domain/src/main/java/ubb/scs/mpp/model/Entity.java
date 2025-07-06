package ubb.scs.mpp.model;

import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.MappedSuperclass;

@MappedSuperclass
public abstract class Entity<ID>  {

    public abstract ID getId();
    public abstract void setId(ID id);
}