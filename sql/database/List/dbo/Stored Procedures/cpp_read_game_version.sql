CREATE PROCEDURE [dbo].[cpp_read_game_version]
AS
  SET NOCOUNT ON
  SELECT  *
  FROM    tgame_version

  RETURN 0
