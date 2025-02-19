package ubb.scs.map.socialNetwork.domain.validators;

public interface Validator <T> {
    void validate(T entity) throws ValidationException;
}