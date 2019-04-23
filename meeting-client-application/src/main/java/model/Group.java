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

    @Override
    public String toString() {
        return (name + " (" + leader + ")");
    }
}
