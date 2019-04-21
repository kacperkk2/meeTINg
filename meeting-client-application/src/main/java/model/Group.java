package model;

import lombok.*;

@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class Group {

    private long id;

    private String name;

    private String leader;

    public String toString() {
        return (id + " " + name + " " + leader);
    }
}
