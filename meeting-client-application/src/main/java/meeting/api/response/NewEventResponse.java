package meeting.api.response;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class NewEventResponse {

    private long id;

    private String name;
}
