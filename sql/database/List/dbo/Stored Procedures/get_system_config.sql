CREATE PROCEDURE [dbo].[get_system_config]
    @item_name VARCHAR(128) = NULL
AS
    IF @item_name IS NULL
        BEGIN
            SELECT  *
            FROM    system_config
        END
    
    ELSE
        BEGIN
            SELECT  *
            FROM    system_config
            WHERE   item_name = @item_name
        END

