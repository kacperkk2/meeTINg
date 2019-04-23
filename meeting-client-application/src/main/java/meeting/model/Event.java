package meeting.model;

import lombok.*;

@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class Event {

    private long id;

    private String name;

    @Override
    public String toString() {
        return name;
    }
}
