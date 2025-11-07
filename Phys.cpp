#include "Phys.h"
#include <algorithm>
#include <cmath>



namespace phys
{

    bool AABB(const Obj& a, const Obj& b)
    {
        const sf::Vector2f apos = a.getPos();
        const sf::Vector2f asize = a.getSize();
        const sf::Vector2f bpos = b.getPos();
        const sf::Vector2f bsize = b.getSize();

        return (apos.x < bpos.x + bsize.x &&
            apos.x + asize.x > bpos.x &&
            apos.y < bpos.y + bsize.y &&
            apos.y + asize.y > bpos.y);
    }

    bool AABB(const Obj& a, const Tile& b)
    {
        const sf::Vector2f apos = a.getPos();
        const sf::Vector2f asize = a.getSize();
        const sf::Vector2f bpos = b.getPos();
        const sf::Vector2f bsize = b.getSizeFromTilemap();

        return (apos.x < bpos.x + bsize.x &&
            apos.x + asize.x > bpos.x &&
            apos.y < bpos.y + bsize.y &&
            apos.y + asize.y > bpos.y);
    }

    bool AABB(const sf::FloatRect& a, const Obj& b)
    {
        const sf::Vector2f apos = a.position;
        const sf::Vector2f asize = a.size;
        const sf::Vector2f bpos = b.getPos();
        const sf::Vector2f bsize = b.getSize();

        return (apos.x < bpos.x + bsize.x &&
            apos.x + asize.x > bpos.x &&
            apos.y < bpos.y + bsize.y &&
            apos.y + asize.y > bpos.y);
    }

    bool AABB(const sf::FloatRect& a, const Tile& b)
    {
        const sf::Vector2f apos = a.position;
        const sf::Vector2f asize = a.size;
        const sf::Vector2f bpos = b.getPos();
        const sf::Vector2f bsize = b.getSizeFromTilemap();

        return (apos.x < bpos.x + bsize.x &&
            apos.x + asize.x > bpos.x &&
            apos.y < bpos.y + bsize.y &&
            apos.y + asize.y > bpos.y);
    }

    float distSq(const Obj* a, const Obj* b)
    {
        sf::Vector2f d = a->getPos() - b->getPos();
        return d.x * d.x + d.y * d.y;
    }

    float distSq(const Obj* a, const Tile* b)
    {
        sf::Vector2f d = a->getPos() - b->getPos();
        return d.x * d.x + d.y * d.y;
    }

    void detectAndSave_Collidable(Obj& a, Obj& b, std::vector<Obj*>& outHits)
    {
        if (!a.isAlive() || !b.isAlive()) return;
        if (AABB(a, b))
            outHits.push_back(&b);
    }

    void detectAndSave_Tile(Obj& a, Tile& b, std::vector<Tile*>& outHits)
    {
        if (!a.isAlive()) return;
        if (AABB(a, b))
            outHits.push_back(&b);
    }

    void sortCollided_Nearest(std::vector<Obj*>& hits, Obj* reference)
    {
        if (!reference || hits.empty()) return;
        std::sort(hits.begin(), hits.end(), [reference](const Obj* a, const Obj* b)
            {
                return distSq(a, reference) < distSq(b, reference);
            });
    }

    void detectAndResolve_Stage_Collidables(Obj& o, std::vector<Obj*>& hits)
    {
        for (auto& h : hits)
        {
            // Simple resolution: push o out of h
            sf::FloatRect or_ = { o.getPos(), o.getSize() };
            sf::FloatRect hr_ = { h->getPos(), h->getSize() };

            if (std::optional<sf::FloatRect> fr = or_.findIntersection(hr_); !fr) continue;

            float dx1 = hr_.position.x + hr_.size.x - or_.position.x;
            float dx2 = or_.position.x + or_.size.x - hr_.position.x;
            float dy1 = hr_.position.y + hr_.size.y - or_.position.y;
            float dy2 = or_.position.y + or_.size.y - hr_.position.y;

            float resolveX = (dx1 < dx2) ? -dx1 : dx2;
            float resolveY = (dy1 < dy2) ? -dy1 : dy2;

            if (std::abs(resolveX) < std::abs(resolveY))
                o.move({ resolveX, 0 });
            else
                o.move({ 0, resolveY });
        }
    }

    void sortCollided_Nearest(std::vector<Tile*>& hits, Obj* reference)
    {

        if (!reference || hits.empty()) return;
        std::sort(hits.begin(), hits.end(), [reference](const Tile* a, const Tile* b)
            {
                return distSq(reference, a) < distSq(reference, b);
            });

    }

    void detectAndResolve_Tilemap_Collisions(Obj& o, std::vector<Tile*>& solidTiles)
    {
        std::vector<Tile*> tmp{};
        for (auto& s : solidTiles)
        {

            detectAndSave_Tile(o, *s, tmp);
        }
        sortCollided_Nearest(tmp, &o);



        for (auto& tile : tmp)
        {
            if (tile->getTileType() != TileType::Solid) continue;

            if (AABB(o, *tile))
            {
                sf::FloatRect or_ = { o.getPos(), o.getSize() };
                sf::FloatRect tr_ = { tile->getPos(), tile->getSizeFromTilemap() };


                if (std::optional<sf::FloatRect> fr = or_.findIntersection(tr_))
                {
                    float resolveX = 0.f;
                    float resolveY = 0.f;

                    if (fr->size.x < fr->size.y)
                        resolveX = (or_.position.x < tr_.position.x) ? -fr->size.x : fr->size.x;
                    else
                        resolveY = (or_.position.y < tr_.position.y) ? -fr->size.y : fr->size.y;

                     o.move({ resolveX, resolveY });

                    if (resolveY < 0 && dynamic_cast<Player*>(&o))
                    {
                        o.core->body->landing = true;

                        o.core->body->vel.y = 0.f;
                        //dynamic_cast<Player*>(&o)->land();
                        //dynamic_cast<Player*>(&o)->collisionOccurred = true;
                        //dynamic_cast<Player*>(&o)->collisionRect = fr.value();
                    }
                }
            }
        }
    }
    void CollidePlayer_Collidables(Obj& player, std::vector<Obj*>& collidables)
    {
        std::vector<Obj*> hits{};

        // Phase 1: Settle collidables
        for (auto& o : collidables)
        {
            if (o == &player) continue;

            for (auto& c : collidables)
            {
                if (c == o || c == &player) continue;
                detectAndSave_Collidable(*o, *c, hits);
            }

            if (!hits.empty())
            {
                sortCollided_Nearest(hits, o);
                detectAndResolve_Stage_Collidables(*o, hits);
                hits.clear();
            }
        }

        // Phase 2: Player vs collidables
        for (auto& obj : collidables)
        {
            if (obj == &player) continue;
            detectAndSave_Collidable(player, *obj, hits);
        }

        if (!hits.empty())
        {
            sortCollided_Nearest(hits, &player);
            detectAndResolve_Stage_Collidables(player, hits);
            hits.clear();
        }
    }

    void CollidePlayer_Tiles(Obj& player, std::vector<Tile*>& tiles)
    {
        std::vector<Tile*> hits{};


        // Phase 2: Player vs collidables
        for (auto& obj : tiles)
        {
            if (obj->getTileType() != TileType::Solid) continue;
            detectAndSave_Tile(player, *obj, hits);
        }

        if (!hits.empty())
        {
            sortCollided_Nearest(hits, &player);
            detectAndResolve_Tilemap_Collisions(player, hits);
            hits.clear();
        }
    }


} // namespace phys