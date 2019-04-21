package api.request;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class GroupListRequest {

    private long userId;
}
