package ubb.scs.map.domain.validators;

import ubb.scs.map.domain.Entity;

import java.util.Optional;

public class EntityValidator implements Validator <Entity> {

    @Override
    public void validate(Entity entity) throws ValidationException {
        if(entity.getId()==null)
            throw new ValidationException("Entity must have an ID");
    }
}
