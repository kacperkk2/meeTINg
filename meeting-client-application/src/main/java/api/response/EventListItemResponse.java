package api.response;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class EventListItemResponse {

    private long id;

    private String name;
}
