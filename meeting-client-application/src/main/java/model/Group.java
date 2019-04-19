package model;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class Group {

    private long id;
    private String name;

    public String toString() {
        return (id + " " + name);
    }
}
